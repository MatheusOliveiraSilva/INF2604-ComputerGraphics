#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "../utils/Vector3D.h"
#include "Ray.h"

// Definir M_PI caso não esteja definido
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Camera {
private:
    Vector3D origin;        // Posição da câmera
    Vector3D lowerLeftCorner;
    Vector3D horizontal;
    Vector3D vertical;
    Vector3D u, v, w;       // Sistema de coordenadas local
    double lensRadius;      // Para efeito de profundidade de campo (não utilizado inicialmente)

public:
    // Construtor padrão
    Camera() 
        : Camera(Vector3D(0, 0, 0), Vector3D(0, 0, -1), Vector3D(0, 1, 0), 90.0, 1.0) {}
    
    // Construtor com parâmetros
    Camera(
        const Vector3D& lookFrom,  // Posição da câmera
        const Vector3D& lookAt,    // Ponto para onde a câmera olha
        const Vector3D& vUp,       // Vetor "para cima" da câmera
        double vFov,               // Campo de visão vertical em graus
        double aspectRatio,        // Proporção da imagem (largura / altura)
        double aperture = 0.0,     // Abertura da lente para profundidade de campo
        double focusDistance = 1.0  // Distância de foco
    ) {
        double theta = vFov * M_PI / 180.0;
        double h = tan(theta / 2.0);
        double viewportHeight = 2.0 * h;
        double viewportWidth = aspectRatio * viewportHeight;
        
        w = (lookFrom - lookAt).normalized();
        u = vUp.cross(w).normalized();
        v = w.cross(u);
        
        origin = lookFrom;
        horizontal = focusDistance * viewportWidth * u;
        vertical = focusDistance * viewportHeight * v;
        lowerLeftCorner = origin - horizontal/2 - vertical/2 - focusDistance * w;
        
        lensRadius = aperture / 2.0;
    }
    
    // Gera um raio para o pixel (s, t)
    Ray getRay(double s, double t) const {
        return Ray(origin, lowerLeftCorner + s*horizontal + t*vertical - origin);
    }
};

#endif // CAMERA_H 