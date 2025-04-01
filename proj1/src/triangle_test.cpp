#include <iostream>
#include <memory>
#include "core/Vector3.h"
#include "core/Ray.h"
#include "core/Color.h"
#include "core/Image.h"
#include "geometry/Triangle.h"
#include "scene/Camera.h"
#include "scene/Scene.h"
#include "scene/Material.h"
#include "lighting/PointLight.h"

int main() {
    // Configurações da imagem
    const int width = 800;
    const int height = 600;
    const double aspect_ratio = static_cast<double>(width) / height;
    
    // Criar a câmera
    Camera camera(
        Point3(0, 0, 5),      // look_from
        Point3(0, 0, 0),      // look_at
        Vector3(0, 1, 0),     // up vector
        45.0,                 // fov (em graus)
        aspect_ratio
    );
    
    // Criar a cena
    Scene scene;
    
    // Adicionar luzes
    scene.add_light(std::make_shared<PointLight>(Point3(5, 5, 5), Color(1, 1, 1), 1.0));
    
    // Criar materiais
    auto red_material = std::make_shared<Material>(
        Color(0.8, 0.2, 0.2) * 0.1,  // ambiente
        Color(0.8, 0.2, 0.2) * 0.7,  // difuso
        Color(1, 1, 1) * 0.5,        // especular
        32.0                         // shininess
    );
    
    auto green_material = std::make_shared<Material>(
        Color(0.2, 0.8, 0.2) * 0.1,  // ambiente
        Color(0.2, 0.8, 0.2) * 0.7,  // difuso
        Color(1, 1, 1) * 0.5,        // especular
        32.0                         // shininess
    );
    
    auto blue_material = std::make_shared<Material>(
        Color(0.2, 0.2, 0.8) * 0.1,  // ambiente
        Color(0.2, 0.2, 0.8) * 0.7,  // difuso
        Color(1, 1, 1) * 0.5,        // especular
        32.0                         // shininess
    );
    
    // Criar uma pirâmide usando 4 triângulos
    Point3 apex(0, 1, 0);
    Point3 base1(-1, -1, -1);
    Point3 base2(1, -1, -1);
    Point3 base3(1, -1, 1);
    Point3 base4(-1, -1, 1);
    
    // Triângulos da pirâmide
    scene.add_object(std::make_shared<Triangle>(apex, base1, base2, red_material.get()));
    scene.add_object(std::make_shared<Triangle>(apex, base2, base3, green_material.get()));
    scene.add_object(std::make_shared<Triangle>(apex, base3, base4, blue_material.get()));
    scene.add_object(std::make_shared<Triangle>(apex, base4, base1, red_material.get()));
    
    // Base da pirâmide (opcional)
    scene.add_object(std::make_shared<Triangle>(base1, base3, base2, green_material.get()));
    scene.add_object(std::make_shared<Triangle>(base1, base4, base3, green_material.get()));
    
    // Criar a imagem
    Image image(width, height);
    
    // Renderizar a cena
    for (int y = 0; y < height; ++y) {
        if (y % (height / 10) == 0) {
            std::cout << "Progresso: " << 100 * y / height << "%" << std::endl;
        }
        
        for (int x = 0; x < width; ++x) {
            double u = static_cast<double>(x) / (width - 1);
            double v = static_cast<double>(height - 1 - y) / (height - 1);
            
            Ray ray = camera.get_ray(u, v);
            Color pixel_color = scene.trace_ray(ray, 5);
            
            image.set_pixel(x, y, pixel_color);
        }
    }
    
    // Salvar a imagem
    image.save_ppm("triangle_test.ppm");
    std::cout << "Imagem salva como triangle_test.ppm" << std::endl;
    
    return 0;
} 