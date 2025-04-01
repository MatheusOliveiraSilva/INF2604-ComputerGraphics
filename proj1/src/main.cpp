#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <string>

#include "core/Vector3.h"
#include "core/Ray.h"
#include "core/Color.h"
#include "core/Image.h"
#include "geometry/Sphere.h"
#include "geometry/Box.h"
#include "geometry/TransformedObject.h"
#include "scene/Camera.h"
#include "scene/Scene.h"
#include "scene/Material.h"
#include "scene/ReflectiveMaterial.h"
#include "lighting/PointLight.h"
#include "utils/Sampler.h"
#include "utils/Transform.h"
#include "geometry/Triangle.h"

int main(int argc, char* argv[]) {
    // Configurações da imagem
    const int width = 800;
    const int height = 600;
    const double aspect_ratio = static_cast<double>(width) / height;
    
    // Número de amostras por pixel para anti-aliasing
    int samples_per_pixel = 4;  // Padrão é 4, pode ser alterado via linha de comando
    
    // Profundidade máxima de recursão para reflexões
    int max_depth = 5;
    
    // Processar argumentos da linha de comando
    if (argc > 1) {
        samples_per_pixel = std::stoi(argv[1]);
    }
    
    std::cout << "Renderizando com " << samples_per_pixel << " amostras por pixel." << std::endl;
    
    // Criar a câmera
    Camera camera(
        Point3(0, 1, 6),     // look_from
        Point3(0, 0, 0),     // look_at
        Vector3(0, 1, 0),    // up vector
        45.0,                // fov (em graus)
        aspect_ratio
    );
    
    // Criar a cena
    Scene scene;
    
    // Adicionar luzes
    scene.add_light(std::make_shared<PointLight>(Point3(5, 5, 5), Color(1, 1, 1), 1.0));
    scene.add_light(std::make_shared<PointLight>(Point3(-5, 3, 3), Color(0.5, 0.5, 0.7), 0.8));
    
    // Criar materiais (importante: são armazenados em variáveis para evitar vazamento de memória)
    auto reflective_material = std::make_shared<ReflectiveMaterial>(
        Color(0.8, 0.8, 0.9) * 0.1,            // ambiente
        Color(0.8, 0.8, 0.9) * 0.1,            // difuso
        Color(1, 1, 1) * 0.8,                  // especular
        64.0,                                  // shininess
        0.8                                    // reflectivity
    );
    
    auto red_material = std::make_shared<Material>(
        Color(0.8, 0.2, 0.2) * 0.1,            // ambiente
        Color(0.8, 0.2, 0.2) * 0.7,            // difuso
        Color(1, 1, 1) * 0.5,                  // especular
        32.0                                   // shininess
    );
    
    auto green_material = std::make_shared<Material>(
        Color(0.2, 0.8, 0.2) * 0.1,            // ambiente
        Color(0.2, 0.8, 0.2) * 0.7,            // difuso
        Color(1, 1, 1) * 0.5,                  // especular
        32.0                                   // shininess
    );
    
    auto floor_material = std::make_shared<Material>(
        Color(0.5, 0.5, 0.5) * 0.1,            // ambiente
        Color(0.5, 0.5, 0.5) * 0.7,            // difuso
        Color(1, 1, 1) * 0.3,                  // especular
        16.0                                   // shininess
    );
    
    auto box_material = std::make_shared<Material>(
        Color(0.3, 0.3, 0.8) * 0.1,            // ambiente
        Color(0.3, 0.3, 0.8) * 0.7,            // difuso
        Color(1, 1, 1) * 0.5,                  // especular
        32.0                                   // shininess
    );
    
    // Adicionar objetos
    // Esfera central reflexiva
    scene.add_object(std::make_shared<Sphere>(
        Point3(0, 0, 0),     // centro
        1.0,                // raio
        reflective_material.get()
    ));
    
    // Esfera vermelha
    scene.add_object(std::make_shared<Sphere>(
        Point3(2, 0, -1),    // centro
        0.7,                // raio
        red_material.get()
    ));
    
    // Esfera verde
    scene.add_object(std::make_shared<Sphere>(
        Point3(-2, 0.3, -1), // centro
        1.0,                // raio
        green_material.get()
    ));
    
    // Chão (caixa grande abaixo da cena)
    scene.add_object(std::make_shared<Box>(
        Point3(-10, -1, -10), // min
        Point3(10, -0.5, 10),  // max
        floor_material.get()
    ));
    
    // Caixa com transformação (rotação)
    auto box = std::make_shared<Box>(
        Point3(-0.5, -0.5, -0.5),
        Point3(0.5, 0.5, 0.5),
        box_material.get()
    );
    
    // Aplicar rotação e translação à caixa
    Transform box_transform = 
        Transform::translate(Vector3(-1.5, 0.5, 1.5)) *
        Transform::rotate_y(0.7) *
        Transform::rotate_x(0.3);
    
    scene.add_object(std::make_shared<TransformedObject>(box, box_transform));
    
    // Adicionar uma pirâmide usando triângulos
    auto yellow_material = std::make_shared<Material>(
        Color(0.8, 0.8, 0.2) * 0.1,            // ambiente
        Color(0.8, 0.8, 0.2) * 0.7,            // difuso
        Color(1, 1, 1) * 0.5,                  // especular
        32.0                                   // shininess
    );
    
    // Criar uma pirâmide usando 4 triângulos
    Point3 apex(0, 2.5, 0);
    Point3 base1(-0.8, 1.5, -0.8);
    Point3 base2(0.8, 1.5, -0.8);
    Point3 base3(0.8, 1.5, 0.8);
    Point3 base4(-0.8, 1.5, 0.8);
    
    // Triângulos da pirâmide
    scene.add_object(std::make_shared<Triangle>(apex, base1, base2, yellow_material.get()));
    scene.add_object(std::make_shared<Triangle>(apex, base2, base3, yellow_material.get()));
    scene.add_object(std::make_shared<Triangle>(apex, base3, base4, yellow_material.get()));
    scene.add_object(std::make_shared<Triangle>(apex, base4, base1, yellow_material.get()));
    
    // Base da pirâmide (opcional)
    scene.add_object(std::make_shared<Triangle>(base1, base3, base2, yellow_material.get()));
    scene.add_object(std::make_shared<Triangle>(base1, base4, base3, yellow_material.get()));
    
    // Adicionar um objeto triangular com transformação
    auto purple_material = std::make_shared<ReflectiveMaterial>(
        Color(0.5, 0.0, 0.5) * 0.1,            // ambiente
        Color(0.5, 0.0, 0.5) * 0.3,            // difuso
        Color(1, 1, 1) * 0.8,                  // especular
        64.0,                                  // shininess
        0.6                                    // reflectivity
    );
    
    // Criar um triângulo e aplicar transformação
    auto triangle = std::make_shared<Triangle>(
        Point3(0, 0, 0),
        Point3(1, 0, 0),
        Point3(0.5, 1, 0),
        purple_material.get()
    );
    
    // Aplicar escala, rotação e translação
    Transform triangle_transform = 
        Transform::translate(Vector3(2.5, 0.5, 2.0)) *
        Transform::rotate_y(0.4) *
        Transform::rotate_x(-0.2) *
        Transform::scale(Vector3(1.5, 1.5, 1.5));
    
    scene.add_object(std::make_shared<TransformedObject>(triangle, triangle_transform));
    
    // Criar a imagem
    Image image(width, height);
    
    // Iniciar timer
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // Para cada pixel, lançar raios
    for (int y = 0; y < height; ++y) {
        // Mostrar progresso a cada 10%
        if (y % (height / 10) == 0) {
            std::cout << "Progresso: " << 100 * y / height << "%" << std::endl;
        }
        
        for (int x = 0; x < width; ++x) {
            Color pixel_color(0, 0, 0);
            
            // Obter amostras para anti-aliasing
            auto samples = Sampler::uniform_samples(samples_per_pixel);
            
            for (const auto& sample : samples) {
                double u = (x + sample.x) / (width - 1);
                double v = (height - 1 - y + sample.y) / (height - 1);  // Coordenadas y invertidas
                
                Ray ray = camera.get_ray(u, v);
                pixel_color += scene.trace_ray(ray, max_depth);
            }
            
            // A cor já será normalizada na função write_color
            image.set_pixel(x, y, pixel_color);
        }
    }
    
    // Finalizar timer e mostrar tempo
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Renderização concluída em " << duration.count() / 1000.0 << " segundos." << std::endl;
    
    // Salvar a imagem
    std::string filename = "output_" + std::to_string(samples_per_pixel) + "spp.ppm";
    image.save_ppm(filename);
    std::cout << "Imagem salva como " << filename << std::endl;
    
    return 0;
} 