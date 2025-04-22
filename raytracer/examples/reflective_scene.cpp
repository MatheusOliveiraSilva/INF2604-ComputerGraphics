#include <iostream>
#include <memory>
#include "../include/core/Vector3.h"
#include "../include/core/Ray.h"
#include "../include/core/Camera.h"
#include "../include/core/Renderer.h"
#include "../include/geometry/Sphere.h"
#include "../include/geometry/Box.h"
#include "../include/geometry/Scene.h"
#include "../include/transform/Translate.h"
#include "../include/transform/Rotate.h"
#include "../include/light/PointLight.h"
#include "../include/light/AmbientLight.h"
#include "../include/material/ReflectiveMaterial.h"

int main() {
    // Configuração da imagem
    int imageWidth = 800;
    int imageHeight = 600;
    int samplesPerPixel = 100; // Aumentando para melhor qualidade da reflexão
    int maxDepth = 5;

    // Configuração da câmera
    Vector3 cameraPosition(0.0f, 4.5f, 12.0f);  // Câmera mais afastada
    Vector3 lookAt(0.0f, 1.0f, 0.0f);           // Mantendo o ponto de mira
    Vector3 up(0.0f, 1.0f, 0.0f);
    float fov = 36.0f;                          // Reduzir um pouco o FOV para compensar o afastamento
    float aspectRatio = float(imageWidth) / float(imageHeight);
    float focalLength = 1.0f;
    
    Camera camera(cameraPosition, lookAt, up, fov, aspectRatio, focalLength);
    
    // Configuração da cena
    Scene scene;
    
    // Materiais coloridos para o ambiente
    std::shared_ptr<Material> blueMaterial = std::make_shared<Material>(
        Color(0.0f, 0.0f, 0.1f),   // ambiente
        Color(0.0f, 0.0f, 0.8f),   // difuso
        Color(0.1f, 0.1f, 0.1f),   // especular
        32.0f                      // brilho
    );
    
    std::shared_ptr<Material> yellowMaterial = std::make_shared<Material>(
        Color(0.1f, 0.1f, 0.0f),   // ambiente
        Color(0.8f, 0.8f, 0.0f),   // difuso
        Color(0.1f, 0.1f, 0.1f),   // especular
        32.0f                      // brilho
    );
    
    std::shared_ptr<Material> whiteMaterial = std::make_shared<Material>(
        Color(0.1f, 0.1f, 0.1f),   // ambiente
        Color(0.8f, 0.8f, 0.8f),   // difuso
        Color(0.1f, 0.1f, 0.1f),   // especular
        32.0f                      // brilho
    );
    
    // Material reflexivo para a esfera central (aumentando a reflexividade para 90%)
    std::shared_ptr<ReflectiveMaterial> mirrorMaterial = std::make_shared<ReflectiveMaterial>(
        Color(0.1f, 0.1f, 0.1f),   // ambiente
        Color(0.05f, 0.05f, 0.05f), // difuso reduzido
        Color(0.9f, 0.9f, 0.9f),   // especular
        128.0f,                    // brilho
        0.9f                       // reflectivity (90% reflexivo)
    );
    
    // Chão (plano branco)
    scene.addObject(new Box(Vector3(-20.0f, -1.0f, -20.0f), Vector3(20.0f, 0.0f, 20.0f), whiteMaterial.get()));
    
    // Apenas duas esferas coloridas (azul e amarela)
    scene.addObject(new Sphere(Vector3(-3.0f, 1.5f, 4.0f), 1.5f, blueMaterial.get()));    // Mais próxima da câmera
    scene.addObject(new Sphere(Vector3(3.0f, 1.5f, 4.0f), 1.5f, yellowMaterial.get()));   // Mais próxima da câmera
    
    // Esfera reflexiva central
    scene.addObject(new Sphere(Vector3(0.0f, 2.0f, 0.0f), 2.0f, mirrorMaterial.get()));
    
    // Configuração da iluminação
    // Luz principal mais brilhante
    PointLight* mainLight = new PointLight(Vector3(0.0f, 8.0f, 0.0f), Color(1.2f, 1.2f, 1.2f));
    scene.addLight(mainLight);
    
    // Luz frontal para melhor iluminação
    PointLight* frontLight = new PointLight(Vector3(0.0f, 3.0f, 8.0f), Color(0.6f, 0.6f, 0.6f));
    scene.addLight(frontLight);
    
    // Luz ambiente mais suave
    scene.setAmbientLight(AmbientLight(0.05f, 0.05f, 0.05f));
    
    // Renderizar a cena
    Renderer renderer(imageWidth, imageHeight, samplesPerPixel, maxDepth);
    std::vector<std::vector<Color>> pixels = renderer.render(scene, camera);
    
    // Salvar a imagem
    renderer.saveToPPM(pixels, "reflective_scene.ppm");
    
    std::cout << "Imagem salva como reflective_scene.ppm" << std::endl;
    
    return 0;
} 