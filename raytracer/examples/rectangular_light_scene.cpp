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
#include "../include/light/RectangularLight.h"
#include "../include/light/AmbientLight.h"

int main() {
    // Configuração da imagem
    int imageWidth = 800;
    int imageHeight = 600;
    int samplesPerPixel = 100; // Aumentando para melhor qualidade com a luz de área
    int maxDepth = 5;          

    // Configuração da câmera
    Vector3 cameraPosition(2.775f, 2.775f, 15.0f);
    Vector3 lookAt(2.775f, 2.775f, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);
    float fov = 35.0f;
    float aspectRatio = float(imageWidth) / float(imageHeight);
    float focalLength = 1.0f;
    
    Camera camera(cameraPosition, lookAt, up, fov, aspectRatio, focalLength);
    
    // Configuração da cena
    Scene scene;
    
    // Materiais
    std::shared_ptr<Material> whiteMaterial = std::make_shared<Material>(
        Color(0.4f, 0.4f, 0.4f),    // ambiente
        Color(0.9f, 0.9f, 0.9f),    // difuso
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> redMaterial = std::make_shared<Material>(
        Color(0.15f, 0.0f, 0.0f),   // ambiente
        Color(0.9f, 0.0f, 0.0f),    // difuso
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> greenMaterial = std::make_shared<Material>(
        Color(0.0f, 0.15f, 0.0f),   // ambiente
        Color(0.0f, 0.9f, 0.0f),    // difuso
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> grayMaterial = std::make_shared<Material>(
        Color(0.15f, 0.15f, 0.15f), // ambiente
        Color(0.4f, 0.4f, 0.4f),    // difuso
        Color(0.0f, 0.0f, 0.0f),    // especular
        0.0f                        // brilho
    );
    
    std::shared_ptr<Material> lightMaterial = std::make_shared<Material>(
        Color(1.0f, 1.0f, 1.0f),    // ambiente
        Color(1.0f, 1.0f, 1.0f),    // difuso
        Color(1.0f, 1.0f, 1.0f),    // especular
        0.0f                        // brilho
    );
    
    // Paredes da cena (Cornell Box)
    scene.addObject(new Box(Vector3(-0.10f, -0.10f, -0.10f), Vector3(5.65f, 5.65f, 0.0f), whiteMaterial.get())); // Fundo
    scene.addObject(new Box(Vector3(-0.10f, -0.1f, 0.0f), Vector3(0.0f, 5.55f, 5.55f), greenMaterial.get()));   // Esquerda
    scene.addObject(new Box(Vector3(5.55f, -0.1f, 0.0f), Vector3(5.65f, 5.55f, 5.55f), redMaterial.get()));     // Direita
    scene.addObject(new Box(Vector3(0.0f, 5.55f, 0.0f), Vector3(5.55f, 5.65f, 5.55f), whiteMaterial.get()));    // Teto
    scene.addObject(new Box(Vector3(-0.1f, -0.10f, 0.0f), Vector3(5.65f, 0.0f, 5.55f), whiteMaterial.get()));   // Chão
    
    // Blocos na cena
    // Bloco grande
    Box* largeBox = new Box(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.65f, 3.30f, 1.65f), grayMaterial.get());
    Rotate* rotatedLargeBox = new Rotate(largeBox, 22.5f, 0.0f, 1.0f, 0.0f);
    Translate* largeBoxPos = new Translate(rotatedLargeBox, 0.65f, 0.0f, 1.30f);
    scene.addObject(largeBoxPos);
    
    // Bloco pequeno
    Box* smallBox = new Box(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.65f, 1.65f, 1.65f), grayMaterial.get());
    Rotate* rotatedSmallBox = new Rotate(smallBox, -18.0f, 0.0f, 1.0f, 0.0f);
    Translate* smallBoxPos = new Translate(rotatedSmallBox, 3.40f, 0.0f, 3.65f);
    scene.addObject(smallBoxPos);
    
    // Objeto luminoso para visualização (um retângulo ou esfera pequena no teto)
    // Cria um retângulo que representa a área da luz
    float lightWidth = 1.0f;
    float lightHeight = 1.0f;
    Vector3 lightCenter(2.775f, 5.54f, 2.775f);
    Vector3 lightMin = lightCenter - Vector3(lightWidth/2, 0.0f, lightHeight/2);
    Vector3 lightMax = lightCenter + Vector3(lightWidth/2, 0.01f, lightHeight/2);
    scene.addObject(new Box(lightMin, lightMax, lightMaterial.get()));
    
    // Configuração da iluminação
    // Luz retangular no teto
    RectangularLight* rectLight = RectangularLight::createRectInCornellBoxCeiling(
        lightWidth, lightHeight, Color(3.0f, 3.0f, 3.0f)
    );
    scene.addLight(rectLight);
    
    // Luz ambiente
    scene.setAmbientLight(AmbientLight(0.15f, 0.15f, 0.15f));
    
    // Renderizar a cena
    Renderer renderer(imageWidth, imageHeight, samplesPerPixel, maxDepth);
    std::vector<std::vector<Color>> pixels = renderer.render(scene, camera);
    
    // Salvar a imagem
    renderer.saveToPPM(pixels, "rectangular_light_scene.ppm");
    
    std::cout << "Imagem salva como rectangular_light_scene.ppm" << std::endl;
    
    return 0;
} 