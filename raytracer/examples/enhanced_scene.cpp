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
    int imageHeight = 600;
    int samplesPerPixel = 100;  // Aumentado ainda mais para qualidade superior
    int maxDepth = 5;          // Mantido para profundidade de reflexão

    // Configuração da câmera para Cornell Box clássica - afastada para mostrar mais da cena
    Vector3 cameraPosition(2.775f, 2.775f, 15.0f);  // Afastando a câmera
    Vector3 lookAt(2.775f, 2.775f, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);
    float fov = 35.0f;        // FOV reduzido para compensar o afastamento
    float aspectRatio = float(imageWidth) / float(imageHeight);
    float focalLength = 1.0f;
    
    Camera camera(cameraPosition, lookAt, up, fov, aspectRatio, focalLength);
    
    // Configuração da cena
    Scene scene;
    
    // Materiais - ajustados para corresponder à imagem
    std::shared_ptr<Material> whiteMaterial = std::make_shared<Material>(
        Color(0.4f, 0.4f, 0.4f),    // ambiente
        Color(0.8f, 0.8f, 0.8f),    // difuso
        Color(0.1f, 0.1f, 0.1f),    // especular
        10.0f                       // brilho
    );
    
    std::shared_ptr<Material> redMaterial = std::make_shared<Material>(
        Color(0.2f, 0.0f, 0.0f),    // ambiente
        Color(0.8f, 0.0f, 0.0f),    // difuso - mais saturado
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> greenMaterial = std::make_shared<Material>(
        Color(0.0f, 0.2f, 0.0f),    // ambiente
        Color(0.0f, 0.8f, 0.0f),    // difuso - mais saturado
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> grayMaterial = std::make_shared<Material>(
        Color(0.2f, 0.2f, 0.2f),    // ambiente
        Color(0.5f, 0.5f, 0.5f),    // difuso - mais claro para melhor visualização
        Color(0.1f, 0.1f, 0.1f),    // especular para dar brilho sutil
        5.0f                        // brilho
    );
    
    // Material para a lâmpada (luz brilhante)
    std::shared_ptr<Material> lightMaterial = std::make_shared<Material>(
        Color(1.0f, 1.0f, 1.0f),    // ambiente
        Color(1.0f, 1.0f, 1.0f),    // difuso
        Color(1.0f, 1.0f, 1.0f),    // especular
        0.0f                        // brilho
    );
    
    // Material metálico para a haste da luminária
    std::shared_ptr<Material> metalMaterial = std::make_shared<Material>(
        Color(0.3f, 0.3f, 0.3f),    // ambiente
        Color(0.7f, 0.7f, 0.7f),    // difuso
        Color(0.9f, 0.9f, 0.9f),    // especular
        80.0f                       // brilho (alto para aparência metálica)
    );
    
    // Paredes da cena (Cornell Box)
    // Parede frontal
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
    
    // Criando a luminária
    
    // Posição da luminária
    Vector3 lightPosition(2.775f, 4.85f, 2.775f);  // Abaixando mais a luz
    
    // Base da luminária no teto (pequeno disco)
    Vector3 basePosition(2.775f, 5.55f, 2.775f);
    scene.addObject(new Box(
        Vector3(basePosition.x - 0.15f, basePosition.y - 0.05f, basePosition.z - 0.15f),
        Vector3(basePosition.x + 0.15f, basePosition.y, basePosition.z + 0.15f),
        metalMaterial.get()
    ));
    
    // Haste da luminária (cilindro fino - aproximado com caixas finas)
    scene.addObject(new Box(
        Vector3(lightPosition.x - 0.025f, lightPosition.y, lightPosition.z - 0.025f),
        Vector3(lightPosition.x + 0.025f, basePosition.y - 0.05f, lightPosition.z + 0.025f),
        metalMaterial.get()
    ));
    
    // Lâmpada (esfera brilhante)
    scene.addObject(new Sphere(lightPosition, 0.15f, lightMaterial.get()));
    
    // Luz pontual no teto - posicionada na lâmpada
    PointLight* pointLight = new PointLight(lightPosition, Color(1.5f, 1.5f, 1.5f));
    scene.addLight(pointLight);
    
    // Segunda fonte de luz secundária para suavizar sombras
    PointLight* ambientLight = new PointLight(Vector3(1.0f, 5.0f, 4.5f), Color(0.1f, 0.1f, 0.1f));
    scene.addLight(ambientLight);
    
    // Luz ambiente - reduzida para destacar sombras
    scene.setAmbientLight(AmbientLight(0.18f, 0.18f, 0.18f));
    
    // Renderizar a cena
    Renderer renderer(imageWidth, imageHeight, samplesPerPixel, maxDepth);
    std::vector<std::vector<Color>> pixels = renderer.render(scene, camera);
    
    // Salvar a imagem
    renderer.saveToPPM(pixels, "cornell_box.ppm");
    
    std::cout << "Imagem salva como cornell_box.ppm" << std::endl;
    
    return 0;
} 