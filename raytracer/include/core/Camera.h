#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "Vector3.h"
#include "Ray.h"

class Camera {
public:
    Vector3 position;       // Posição da câmera
    Vector3 lookAt;         // Ponto para onde a câmera olha
    Vector3 up;             // Vetor "up" da câmera
    float fov;              // Campo de visão (em graus)
    float aspectRatio;      // Razão de aspecto (largura/altura)
    float focalLength;      // Distância focal

    Vector3 u, v, w;        // Base ortogonal da câmera
    float viewportHeight;   // Altura do viewport
    float viewportWidth;    // Largura do viewport

    // Construtor padrão
    Camera() 
        : position(0, 0, 0), lookAt(0, 0, -1), up(0, 1, 0),
          fov(90.0f), aspectRatio(1.0f), focalLength(1.0f) {
        initialize();
    }

    // Construtor personalizado
    Camera(const Vector3& position, const Vector3& lookAt, const Vector3& up,
           float fov, float aspectRatio, float focalLength)
        : position(position), lookAt(lookAt), up(up),
          fov(fov), aspectRatio(aspectRatio), focalLength(focalLength) {
        initialize();
    }

    // Gera um raio para determinadas coordenadas de pixel (u,v) normalizadas [0,1]
    Ray getRay(float u, float v) const {
        Vector3 horizontal = viewportWidth * this->u;
        Vector3 vertical = viewportHeight * this->v;
        Vector3 lowerLeftCorner = position - horizontal/2 - vertical/2 - focalLength * this->w;
        
        Vector3 direction = lowerLeftCorner + u*horizontal + v*vertical - position;
        return Ray(position, normalize(direction));
    }

private:
    // Inicializa os vetores da base ortogonal e dimensões do viewport
    void initialize() {
        // Converter FOV de graus para radianos
        float theta = fov * M_PI / 180.0f;
        float halfHeight = tan(theta / 2);
        viewportHeight = 2.0f * halfHeight;
        viewportWidth = aspectRatio * viewportHeight;

        // Criar base ortogonal
        w = normalize(position - lookAt);  // Direção oposta ao lookAt
        u = normalize(cross(up, w));       // Vetor direita
        v = cross(w, u);                   // Vetor "up" real
    }
};

#endif // CAMERA_H 