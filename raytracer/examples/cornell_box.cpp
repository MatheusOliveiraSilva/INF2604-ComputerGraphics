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

int main() {
    // Configuração da imagem
    int imageWidth = 800;
    int imageHeight = 600;
    int samplesPerPixel = 25;

    // Configuração da câmera conforme especificação
    Vector3 cameraPosition(2.775f, 3.200f, 12.775f);
    Vector3 lookAt(2.775f, 2.775f, 2.775f);
    Vector3 up(0.0f, 1.0f, 0.0f);
    float fov = 50.0f;
    float aspectRatio = float(imageWidth) / float(imageHeight);
    float focalLength = 1.0f;
    
    Camera camera(cameraPosition, lookAt, up, fov, aspectRatio, focalLength);
    
    // Configuração da cena
    Scene scene;
    
    // Materiais
    std::shared_ptr<Material> whiteMaterial = std::make_shared<Material>(
        Color(0.3f, 0.3f, 0.3f),    // ambiente
        Color(0.7f, 0.7f, 0.7f),    // difuso
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> redMaterial = std::make_shared<Material>(
        Color(0.3f, 0.0f, 0.0f),    // ambiente
        Color(0.7f, 0.0f, 0.0f),    // difuso 
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> greenMaterial = std::make_shared<Material>(
        Color(0.0f, 0.3f, 0.0f),    // ambiente
        Color(0.0f, 0.7f, 0.0f),    // difuso
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> grayMaterial = std::make_shared<Material>(
        Color(0.2f, 0.2f, 0.2f),    // ambiente
        Color(0.5f, 0.5f, 0.5f),    // difuso
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> lightMaterial = std::make_shared<Material>(
        Color(0.8f, 0.8f, 0.8f),    // ambiente
        Color(0.8f, 0.8f, 0.8f),    // difuso
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    // Paredes da cena conforme especificação
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
    
    // Blocos dentro da cena
    // Bloco pequeno (com rotação)
    Box* smallBox = new Box(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.65f, 1.65f, 0.30f), grayMaterial.get());
    Rotate* rotatedSmallBox = new Rotate(smallBox, -18.0f, 0.0f, 1.0f, 0.0f);
    Translate* smallBoxPos = new Translate(rotatedSmallBox, 3.40f, 1.2f, 3.65f);
    scene.addObject(smallBoxPos);
    
    // Bloco grande (com rotação)
    Box* largeBox = new Box(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.65f, 3.30f, 1.65f), grayMaterial.get());
    Rotate* rotatedLargeBox = new Rotate(largeBox, 22.5f, 0.0f, 1.0f, 0.0f);
    Translate* largeBoxPos = new Translate(rotatedLargeBox, 0.65f, 0.0f, 1.30f);
    scene.addObject(largeBoxPos);
    
    // Fonte de luz pontual
    Vector3 lightPosition(2.775f, 5.55f, 2.775f);
    PointLight* light = new PointLight(lightPosition, Color(0.7f, 0.7f, 0.7f));
    scene.addLight(light);
    
    // Luminária (esfera)
    scene.addObject(new Sphere(lightPosition, 0.1f, lightMaterial.get()));
    
    // Luz ambiente
    scene.setAmbientLight(AmbientLight(0.3f, 0.3f, 0.3f));
    
    // Renderizar a cena
    Renderer renderer(imageWidth, imageHeight, samplesPerPixel);
    std::vector<std::vector<Color>> pixels = renderer.render(scene, camera);
    
    // Salvar a imagem
    renderer.saveToPPM(pixels, "cornell_box.ppm");
    
    std::cout << "Imagem salva como cornell_box.ppm" << std::endl;
    
    return 0;
} 