#include <iostream>
#include <memory>
#include <limits>

#include "../include/vec3.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include "../include/plane.h"
#include "../include/camera.h"
#include "../include/material.h"
#include "../include/light.h"
#include "../include/scene.h"
#include "../include/renderer.h"

int main() {
    // Configuração do renderizador
    Renderer renderer(800, 1.0);  // Imagem quadrada 800x800
    
    // Configuração da câmera
    Camera camera(
        Point3(0, 2, 6),    // Posição da câmera
        Point3(0, 0, 0),    // Ponto para onde a câmera olha
        Vec3(0, 1, 0),      // Vetor "up"
        45.0                // Campo de visão em graus
    );
    
    // Configuração da cena
    Scene scene;
    scene.background_color = Color(0, 0, 0);  // Fundo preto
    
    // Criação dos materiais
    auto red_material = std::make_shared<Material>(
        Color(0.1, 0.0, 0.0),     // Ambiente
        Color(0.8, 0.0, 0.0),     // Difuso
        Color(0.8, 0.8, 0.8),     // Especular
        32.0                      // Brilho
    );
    
    auto plane_material = std::make_shared<Material>(
        Color(0.1, 0.1, 0.1),     // Ambiente
        Color(0.8, 0.8, 0.8),     // Difuso
        Color(0.0, 0.0, 0.0),     // Especular
        1.0                       // Brilho
    );
    
    // Adição de objetos à cena
    scene.add_object(std::make_shared<Sphere>(
        Point3(0, 0.7, 0),        // Centro da esfera
        0.7,                      // Raio
        red_material              // Material
    ));
    
    scene.add_object(std::make_shared<Plane>(
        Point3(0, 0, 0),          // Ponto no plano
        Vec3(0, 1, 0),            // Normal do plano
        plane_material            // Material
    ));
    
    // Adição de luzes à cena
    scene.add_light(Light(
        Point3(5, 5, 5),          // Posição da luz
        Color(1, 1, 1),           // Cor da luz
        1.0                       // Intensidade
    ));
    
    // Renderiza a cena
    std::string output_file = "output.ppm";
    renderer.render(scene, camera, output_file);
    
    std::cout << "Imagem salva como " << output_file << std::endl;
    
    return 0;
} 