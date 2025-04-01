#include <iostream>
#include <memory>
#include "core/Vector3.h"
#include "core/Ray.h"
#include "core/Color.h"
#include "core/Image.h"
#include "geometry/Sphere.h"
#include "scene/Camera.h"
#include "scene/Material.h"

// Função simplificada para testar interseção com uma esfera
bool hit_sphere(const Point3& center, double radius, const Ray& ray) {
    Vector3 oc = ray.origin() - center;
    auto a = ray.direction().length_squared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    return (discriminant > 0);
}

// Função simplificada para calcular cor
Color ray_color(const Ray& ray) {
    Point3 sphere_center(0, 0, -1);
    
    if (hit_sphere(sphere_center, 0.5, ray)) {
        return Color(1, 0, 0); // Esfera vermelha
    }
    
    Vector3 unit_direction = normalize(ray.direction());
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0); // Gradiente de fundo
}

int main() {
    // Configurações da imagem
    const int width = 400;
    const int height = 200;
    
    // Configurações da câmera
    auto aspect_ratio = static_cast<double>(width) / height;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;
    
    auto origin = Point3(0, 0, 0);
    auto horizontal = Vector3(viewport_width, 0, 0);
    auto vertical = Vector3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3(0, 0, focal_length);
    
    // Criar a imagem
    Image image(width, height);
    
    // Renderizar
    for (int y = 0; y < height; ++y) {
        std::cout << "Linha: " << y << "/" << height << std::endl;
        
        for (int x = 0; x < width; ++x) {
            auto u = static_cast<double>(x) / (width - 1);
            auto v = static_cast<double>(height - 1 - y) / (height - 1); // y invertido
            
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            Color pixel_color = ray_color(ray);
            
            image.set_pixel(x, y, pixel_color);
        }
    }
    
    // Salvar a imagem
    image.save_ppm("simple_output.ppm");
    std::cout << "Imagem salva como simple_output.ppm" << std::endl;
    
    return 0;
} 