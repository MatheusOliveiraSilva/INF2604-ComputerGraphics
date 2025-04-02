#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "../include/core/Scene.h"
#include "../include/core/Camera.h"
#include "../include/core/Renderer.h"
#include "../include/geometry/Sphere.h"
#include "../include/geometry/Box.h"
#include "../include/material/Material.h"
#include "../include/light/Light.h"

// Função para criar uma cena de teste com algumas esferas e caixas
Scene createTestScene() {
    Scene scene;
    
    // Materiais
    auto redMaterial = std::make_shared<PhongMaterial>(
        Color(0.1, 0.0, 0.0),  // ambiente
        Color(0.7, 0.1, 0.1),  // difuso
        Color(0.5, 0.5, 0.5),  // especular
        32.0                   // brilho
    );
    
    auto greenMaterial = std::make_shared<PhongMaterial>(
        Color(0.0, 0.1, 0.0),
        Color(0.1, 0.7, 0.1),
        Color(0.5, 0.5, 0.5),
        32.0
    );
    
    auto blueMaterial = std::make_shared<PhongMaterial>(
        Color(0.0, 0.0, 0.1),
        Color(0.1, 0.1, 0.7),
        Color(0.5, 0.5, 0.5),
        32.0
    );
    
    auto yellowMaterial = std::make_shared<PhongMaterial>(
        Color(0.1, 0.1, 0.0),
        Color(0.7, 0.7, 0.1),
        Color(0.5, 0.5, 0.5),
        32.0
    );
    
    auto groundMaterial = std::make_shared<PhongMaterial>(
        Color(0.1, 0.1, 0.1),
        Color(0.6, 0.6, 0.6),
        Color(0.0, 0.0, 0.0),
        1.0
    );
    
    // Objetos
    // Esferas
    auto sphere1 = std::make_shared<Sphere>(Vector3D(0, 1, 0), 1.0, redMaterial);
    auto sphere2 = std::make_shared<Sphere>(Vector3D(-2, 0.5, -1), 0.5, greenMaterial);
    auto sphere3 = std::make_shared<Sphere>(Vector3D(2, 0.5, -1), 0.5, blueMaterial);
    
    // Caixas
    auto box1 = std::make_shared<Box>(Vector3D(-1, 0, -2), Vector3D(1, 2, -1), yellowMaterial);
    
    // Chão (esfera grande)
    auto ground = std::make_shared<Sphere>(Vector3D(0, -100.5, 0), 100.0, groundMaterial);
    
    // Adiciona objetos à cena
    scene.addObject(sphere1);
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    scene.addObject(box1);
    scene.addObject(ground);
    
    // Luzes
    auto light1 = std::make_shared<PointLight>(Vector3D(10, 10, 10), Color(1.0, 1.0, 1.0));
    auto light2 = std::make_shared<PointLight>(Vector3D(-10, 10, 0), Color(0.5, 0.5, 0.5));
    
    // Adiciona luzes à cena
    scene.addLight(light1);
    scene.addLight(light2);
    
    // Define a luz ambiente global
    scene.setAmbientLight(Color(0.1, 0.1, 0.1));
    
    return scene;
}

int main(int argc, char* argv[]) {
    // Parâmetros de renderização
    int width = 800;
    int height = 600;
    int samplesPerPixel = 4;
    std::string outputFile = "output/output.ppm";
    
    // Processa argumentos da linha de comando
    if (argc > 1) {
        outputFile = argv[1];
    }
    
    if (argc > 2) {
        samplesPerPixel = std::stoi(argv[2]);
    }
    
    // Configura a câmera
    Vector3D lookFrom(0, 1, 5);
    Vector3D lookAt(0, 1, 0);
    Vector3D vUp(0, 1, 0);
    double fov = 60.0;
    double aspectRatio = static_cast<double>(width) / height;
    Camera camera(lookFrom, lookAt, vUp, fov, aspectRatio);
    
    // Cria a cena de teste
    Scene scene = createTestScene();
    
    // Cria o renderizador
    Renderer renderer(width, height, samplesPerPixel);
    
    // Renderiza a cena
    std::cout << "Renderizando cena com " << samplesPerPixel << " amostras por pixel..." << std::endl;
    renderer.render(scene, camera, outputFile);
    std::cout << "Imagem salva em " << outputFile << std::endl;
    
    return 0;
} 