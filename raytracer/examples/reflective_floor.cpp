#include <iostream>
#include <memory>
#include "../include/core/Vector3.h"
#include "../include/core/Ray.h"
#include "../include/core/Camera.h"
#include "../include/core/Renderer.h"
#include "../include/geometry/Sphere.h"
#include "../include/geometry/Box.h"
#include "../include/geometry/Scene.h"
#include "../include/light/PointLight.h"
#include "../include/light/AmbientLight.h"
#include "../include/material/ReflectiveMaterial.h"

// Exemplo simples que demonstra um piso reflexivo e algumas esferas coloridas.
// A ideia é que as esferas apareçam refletidas no chão, evidenciando o uso de
// ReflectiveMaterial para superfícies planas.
int main() {
    // Resolução da imagem
    int imageWidth  = 800;
    int imageHeight = 600;
    int samplesPerPixel = 100; // qualidade razoável para reflexos suaves
    int maxDepth = 5;          // profundidade recursiva p/ reflexos

    // Configuração da câmera (um pouco acima do solo, olhando para as esferas)
    Vector3 cameraPos(0.0f, 3.5f, 10.0f);
    Vector3 lookAt(0.0f, 1.0f, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);
    float fov = 36.0f;
    float aspectRatio = static_cast<float>(imageWidth) / imageHeight;
    Camera camera(cameraPos, lookAt, up, fov, aspectRatio, 1.0f);

    // Cena
    Scene scene;

    // Materiais difusos coloridos
    auto redMat = std::make_shared<Material>(
        Color(0.1f, 0.0f, 0.0f),   // ambiente
        Color(0.8f, 0.0f, 0.0f),   // difuso
        Color(0.1f, 0.1f, 0.1f),   // especular
        32.0f                      // brilho
    );

    auto greenMat = std::make_shared<Material>(
        Color(0.0f, 0.1f, 0.0f),
        Color(0.0f, 0.8f, 0.0f),
        Color(0.1f, 0.1f, 0.1f),
        32.0f
    );

    auto blueMat = std::make_shared<Material>(
        Color(0.0f, 0.0f, 0.1f),
        Color(0.0f, 0.0f, 0.8f),
        Color(0.1f, 0.1f, 0.1f),
        32.0f
    );

    // Piso reflexivo (80 %)
    auto reflectiveFloor = std::make_shared<ReflectiveMaterial>(
        Color(0.02f, 0.02f, 0.02f), // ambiente
        Color(0.2f, 0.2f, 0.2f),    // difuso cinza
        Color(0.9f, 0.9f, 0.9f),    // especular forte
        64.0f,                      // shininess
        0.8f                        // reflectivity 80 %
    );

    // Geometria ----------------------------------------------------------------

    // Piso como um Box bem fino (y = 0 é a superfície refletiva)
    scene.addObject(new Box({-30.0f, -0.01f, -30.0f}, {30.0f, 0.0f, 30.0f}, reflectiveFloor.get()));

    // Três esferas coloridas
    scene.addObject(new Sphere({-4.0f, 1.5f, 0.0f}, 1.5f, redMat.get()));
    scene.addObject(new Sphere({0.0f, 1.5f, -3.0f}, 1.5f, greenMat.get()));
    scene.addObject(new Sphere({4.0f, 1.5f, 1.0f}, 1.5f, blueMat.get()));

    // Iluminação ----------------------------------------------------------------
    // Luz principal vinda de cima
    scene.addLight(new PointLight({0.0f, 10.0f, 0.0f}, {1.2f, 1.2f, 1.2f}));
    // Luz de preenchimento frontal
    scene.addLight(new PointLight({0.0f, 4.0f, 8.0f}, {0.6f, 0.6f, 0.6f}));

    scene.setAmbientLight({0.05f, 0.05f, 0.05f});

    // Renderização ----------------------------------------------------------------
    Renderer renderer(imageWidth, imageHeight, samplesPerPixel, maxDepth);
    auto pixels = renderer.render(scene, camera);
    renderer.saveToPPM(pixels, "reflective_floor_scene.ppm");
    std::cout << "Imagem salva como reflective_floor_scene.ppm" << std::endl;

    return 0;
} 