#ifndef RAY_H
#define RAY_H

#include "../utils/Vector3D.h"

class Ray {
public:
    Vector3D origin;      // Origem do raio
    Vector3D direction;   // Direção do raio (normalizada)

    // Construtores
    Ray() = default;
    
    Ray(const Vector3D& origin, const Vector3D& direction)
        : origin(origin), direction(direction.normalized()) {}
    
    // Calcula ponto ao longo do raio: o + t*d
    Vector3D pointAtParameter(double t) const {
        return origin + direction * t;
    }
};

#endif // RAY_H 