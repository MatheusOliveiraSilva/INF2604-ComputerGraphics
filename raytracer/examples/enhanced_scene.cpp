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
#include "../include/light/RectLight.h"
#include "../include/light/AmbientLight.h"
#include "../include/material/ReflectiveMaterial.h"

int main() {
    // Configuração da imagem - aumentando amostras por pixel para maior qualidade
    int imageWidth = 800;
    int imageHeight = 800; // Alterado para formato quadrado como na imagem de referência
    int samplesPerPixel = 1000;  // Aumentado ainda mais para reduzir ruído
    int maxDepth = 5;          // Mantido para profundidade de reflexão

    // Configuração da câmera para Cornell Box clássica
    Vector3 cameraPosition(2.775f, 2.775f, 15.0f);
    Vector3 lookAt(2.775f, 2.775f, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);
    float fov = 35.0f;
    float aspectRatio = float(imageWidth) / float(imageHeight);
    float focalLength = 1.0f;
    
    Camera camera(cameraPosition, lookAt, up, fov, aspectRatio, focalLength);
    
    // Configuração da cena
    Scene scene;
    
    // Materiais ajustados para corresponder à imagem de referência
    std::shared_ptr<Material> whiteMaterial = std::make_shared<Material>(
        Color(0.4f, 0.4f, 0.4f),    // ambiente
        Color(0.9f, 0.9f, 0.9f),    // difuso - mais brilhante
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> redMaterial = std::make_shared<Material>(
        Color(0.15f, 0.0f, 0.0f),    // ambiente
        Color(0.9f, 0.0f, 0.0f),     // difuso - mais saturado
        Color(0.0f, 0.0f, 0.0f),     // especular
        0.0f                         // brilho
    );
    
    std::shared_ptr<Material> greenMaterial = std::make_shared<Material>(
        Color(0.0f, 0.15f, 0.0f),    // ambiente
        Color(0.0f, 0.9f, 0.0f),     // difuso - mais saturado
        Color(0.0f, 0.0f, 0.0f),     // especular
        0.0f                         // brilho
    );
    
    std::shared_ptr<Material> grayMaterial = std::make_shared<Material>(
        Color(0.15f, 0.15f, 0.15f),  // ambiente
        Color(0.4f, 0.4f, 0.4f),     // difuso - mais escuro para corresponder à referência
        Color(0.0f, 0.0f, 0.0f),     // especular
        0.0f                         // brilho
    );
    
    // Material para a lâmpada (luz brilhante)
    std::shared_ptr<Material> lightMaterial = std::make_shared<Material>(
        Color(1.0f, 1.0f, 1.0f),    // ambiente
        Color(1.0f, 1.0f, 1.0f),    // difuso
        Color(1.0f, 1.0f, 1.0f),    // especular
        0.0f                        // brilho
    );
    
    // Paredes da cena (Cornell Box)
    // Parede frontal (fundo)
    scene.addObject(new Box(Vector3(-0.10f, -0.10f, -0.10f), Vector3(5.65f, 5.65f, 0.0f), whiteMaterial.get()));
    
    // Parede à esquerda (verde)
    scene.addObject(new Box(Vector3(-0.10f, -0.1f, 0.0f), Vector3(0.0f, 5.55f, 5.55f), greenMaterial.get()));
    
    // Parede à direita (vermelha)
    scene.addObject(new Box(Vector3(5.55f, -0.1f, 0.0f), Vector3(5.65f, 5.55f, 5.55f), redMaterial.get()));
    
    // Teto
    scene.addObject(new Box(Vector3(0.0f, 5.55f, 0.0f), Vector3(5.55f, 5.65f, 5.55f), whiteMaterial.get()));
    
    // Chão
    scene.addObject(new Box(Vector3(-0.1f, -0.10f, 0.0f), Vector3(5.65f, 0.0f, 5.55f), whiteMaterial.get()));
    
    // Blocos dentro da cena (ajustados para corresponder à imagem)
    // Bloco grande (com rotação)
    Box* largeBox = new Box(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.65f, 3.30f, 1.65f), grayMaterial.get());
    Rotate* rotatedLargeBox = new Rotate(largeBox, 22.5f, 0.0f, 1.0f, 0.0f);
    Translate* largeBoxPos = new Translate(rotatedLargeBox, 0.65f, 0.0f, 1.30f);
    scene.addObject(largeBoxPos);
    
    // Bloco pequeno (com rotação)
    Box* smallBox = new Box(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.65f, 1.65f, 1.65f), grayMaterial.get());
    Rotate* rotatedSmallBox = new Rotate(smallBox, -18.0f, 0.0f, 1.0f, 0.0f);
    Translate* smallBoxPos = new Translate(rotatedSmallBox, 3.40f, 0.0f, 3.65f);
    scene.addObject(smallBoxPos);
    
    // Lâmpada simples embutida no teto (pequena esfera)
    Vector3 lightPosition(2.775f, 5.45f, 2.775f);  // Posição da luz logo abaixo do teto
    scene.addObject(new Sphere(lightPosition, 0.1f, lightMaterial.get()));
    
    // Fonte de luz de área para criar a iluminação suave (simulação de uma área)
    // Usamos múltiplas luzes pontuais em uma área para criar o efeito de luz difusa
    float areaRadius = 0.8f;
    int areaLightSamples = 8;
    float intensityPerSample = 0.5f / areaLightSamples;
    
    // Luz central mais intensa
    PointLight* centralLight = new PointLight(lightPosition, Color(1.0f, 1.0f, 1.0f));
    scene.addLight(centralLight);
    
    // Luzes auxiliares em um padrão circular para simular uma fonte de luz de área
    for (int i = 0; i < areaLightSamples; i++) {
        float angle = 2.0f * M_PI * i / areaLightSamples;
        float x = lightPosition.x + areaRadius * cos(angle);
        float z = lightPosition.z + areaRadius * sin(angle);
        
        Vector3 samplePos(x, lightPosition.y, z);
        PointLight* areaLight = new PointLight(samplePos, Color(intensityPerSample, intensityPerSample, intensityPerSample));
        scene.addLight(areaLight);
    }
    
    // Luz ambiente - ajustada para balancear a cena
    scene.setAmbientLight(AmbientLight(0.15f, 0.15f, 0.15f));
    
    // Renderizar a cena
    Renderer renderer(imageWidth, imageHeight, samplesPerPixel, maxDepth);
    std::vector<std::vector<Color>> pixels = renderer.render(scene, camera);
    
    // Salvar a imagem
    renderer.saveToPPM(pixels, "cornell_box_reference.ppm");
    
    std::cout << "Imagem salva como cornell_box_reference.ppm" << std::endl;
    
    return 0;
} 