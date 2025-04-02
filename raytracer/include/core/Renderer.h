#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>
#include <limits>
#include "Scene.h"
#include "Camera.h"
#include "../utils/Color.h"
#include "../material/Material.h"

// Gerador de números aleatórios
inline double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

class Renderer {
private:
    int width;                 // Largura da imagem em pixels
    int height;                // Altura da imagem em pixels
    int samplesPerPixel;       // Número de amostras por pixel para antialiasing
    int maxDepth;              // Profundidade máxima de recursão
    
    // Calcula a cor para um raio específico
    Color rayColor(const Ray& ray, const Scene& scene, int depth) const {
        // Se atingiu a profundidade máxima, retorna preto
        if (depth <= 0) return Colors::BLACK;
        
        HitRecord record;
        
        // Verifica se o raio atinge algum objeto
        if (scene.hit(ray, 0.001, std::numeric_limits<double>::infinity(), record)) {
            // Cálculo de iluminação - modelo Phong
            return shadingPhong(ray, record, scene);
        }
        
        // Se não atingiu nada, retorna cor de fundo (gradiente)
        Vector3D unitDirection = ray.direction;
        double t = 0.5 * (unitDirection.y + 1.0);
        return Colors::WHITE * (1.0 - t) + Color(0.5, 0.7, 1.0) * t;
    }
    
    // Implementação do modelo de iluminação Phong
    Color shadingPhong(const Ray& ray, const HitRecord& hit, const Scene& scene) const {
        // Componente ambiente global
        const Color& ambientGlobal = scene.getAmbientLight();
        
        // Propriedades do material
        const std::shared_ptr<Material>& material = hit.material;
        Color ambient = material->getAmbient();
        Color diffuse = material->getDiffuse();
        Color specular = material->getSpecular();
        double shininess = material->getShininess();
        
        // Inicializa com componente ambiente
        Color result = ambient * ambientGlobal;
        
        // Direção para o observador
        Vector3D viewDir = (ray.origin - hit.point).normalized();
        
        // Para cada fonte de luz
        for (const auto& light : scene.getLights()) {
            // Direção e distância até a luz
            Vector3D lightDir = light->getDirection(hit.point);
            double lightDistance = light->getDistance(hit.point);
            
            // Verifica sombra: se houver algo entre o ponto e a luz
            bool inShadow = false;
            Ray shadowRay(hit.point + hit.normal * 0.001, lightDir);
            HitRecord shadowRecord;
            
            if (scene.hit(shadowRay, 0.001, lightDistance, shadowRecord)) {
                inShadow = true;
            }
            
            // Se não estiver em sombra, calcula a cor
            if (!inShadow) {
                // Intensidade da luz no ponto
                Color lightIntensity = light->getIntensity(hit.point);
                
                // Componente difuso: cos(ângulo) entre normal e luz
                double diffuseFactor = std::max(0.0, hit.normal.dot(lightDir));
                
                // Componente especular: reflexão da luz
                Vector3D reflectDir = lightDir * -1.0 + hit.normal * 2.0 * hit.normal.dot(lightDir);
                reflectDir.normalize();
                double specularFactor = std::pow(std::max(0.0, viewDir.dot(reflectDir)), shininess);
                
                // Acumula contribuições
                result += diffuse * lightIntensity * diffuseFactor;
                result += specular * lightIntensity * specularFactor;
            }
        }
        
        // Limita os valores entre 0 e 1
        result.clamp();
        return result;
    }

public:
    Renderer(int width, int height, int samplesPerPixel = 1, int maxDepth = 50)
        : width(width), height(height), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth) {}
    
    // Renderiza a cena e salva em um arquivo PPM
    void render(const Scene& scene, const Camera& camera, const std::string& outputFile) const {
        // Abre o arquivo de saída
        std::ofstream out(outputFile);
        
        // Cabeçalho do arquivo PPM
        out << "P3\n" << width << " " << height << "\n255\n";
        
        // Para cada pixel da imagem
        for (int j = height - 1; j >= 0; --j) {
            std::cerr << "\rLinhas restantes: " << j << ' ' << std::flush;
            
            for (int i = 0; i < width; ++i) {
                Color pixelColor(0, 0, 0);
                
                // Amostragem múltipla para antialiasing
                for (int s = 0; s < samplesPerPixel; ++s) {
                    // Coordenadas de pixel aleatórias dentro do pixel
                    double u = (i + randomDouble()) / (width - 1);
                    double v = (j + randomDouble()) / (height - 1);
                    
                    // Gera raio da câmera passando pelo pixel
                    Ray ray = camera.getRay(u, v);
                    
                    // Acumula a cor
                    pixelColor += rayColor(ray, scene, maxDepth);
                }
                
                // Média das amostras e correção gamma
                pixelColor = pixelColor * (1.0 / samplesPerPixel);
                pixelColor.r = sqrt(pixelColor.r);
                pixelColor.g = sqrt(pixelColor.g);
                pixelColor.b = sqrt(pixelColor.b);
                
                // Escreve o valor do pixel
                out << pixelColor << "\n";
            }
        }
        
        std::cerr << "\nRenderização concluída.\n";
    }
};

#endif // RENDERER_H 