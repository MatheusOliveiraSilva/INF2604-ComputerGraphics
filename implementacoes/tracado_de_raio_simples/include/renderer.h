#ifndef RENDERER_H
#define RENDERER_H

#include "scene.h"
#include "camera.h"
#include <string>
#include <fstream>
#include <iostream>

class Renderer {
public:
    int image_width;
    int image_height;
    double aspect_ratio;

    Renderer(int width = 800, double aspect = 16.0 / 9.0)
        : image_width(width), aspect_ratio(aspect) {
        image_height = static_cast<int>(image_width / aspect_ratio);
    }

    // Calcula a cor para um raio específico
    Color ray_color(const Ray& ray, const Scene& scene, int depth = 50) const {
        // Verifica a interseção com objetos da cena
        HitRecord rec;
        if (scene.hit(ray, 0.001, std::numeric_limits<double>::infinity(), rec)) {
            Color color = rec.material->ambient; // Componente ambiente
            
            // Adiciona a contribuição de cada luz
            for (const auto& light : scene.lights) {
                // Verifica se o ponto está em sombra
                if (!scene.is_shadowed(rec.point, light)) {
                    Vec3 light_dir = light.direction_from(rec.point);
                    double diff = std::max(0.0, dot(rec.normal, light_dir));

                    // Componente difusa
                    color += diff * rec.material->diffuse * light.color * light.intensity;

                    // Componente especular (modelo de Phong)
                    if (diff > 0) {
                        Vec3 view_dir = -ray.direction.normalized();
                        Vec3 reflect_dir = 2 * dot(rec.normal, light_dir) * rec.normal - light_dir;
                        double spec = std::pow(std::max(0.0, dot(view_dir, reflect_dir)), rec.material->shininess);
                        color += spec * rec.material->specular * light.color * light.intensity;
                    }
                }
            }
            
            return color;
        }
        
        // Não atingiu nada, retorna a cor de fundo
        return scene.background_color;
    }

    // Renderiza a cena usando ray tracing
    void render(const Scene& scene, const Camera& camera, const std::string& filename) const {
        std::ofstream output(filename);
        
        if (!output.is_open()) {
            std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
            return;
        }
        
        // Cabeçalho do arquivo PPM
        output << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        
        // Renderiza cada pixel
        for (int j = image_height - 1; j >= 0; --j) {
            std::cerr << "\rRenderizando: " << (image_height - j) * 100 / image_height << "% " << std::flush;
            
            for (int i = 0; i < image_width; ++i) {
                double u = double(i) / (image_width - 1);
                double v = double(j) / (image_height - 1);
                
                Ray ray = camera.get_ray(u, v);
                Color pixel_color = ray_color(ray, scene);
                
                // Escreve a cor do pixel (com correção de gamma)
                int r = static_cast<int>(255.999 * std::min(1.0, sqrt(pixel_color.x)));
                int g = static_cast<int>(255.999 * std::min(1.0, sqrt(pixel_color.y)));
                int b = static_cast<int>(255.999 * std::min(1.0, sqrt(pixel_color.z)));
                
                output << r << ' ' << g << ' ' << b << '\n';
            }
        }
        
        std::cerr << "\nRenderização concluída.\n";
        output.close();
    }
};

#endif // RENDERER_H 