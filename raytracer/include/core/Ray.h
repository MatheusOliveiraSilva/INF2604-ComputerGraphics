#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    // Construtores
    Ray() {}
    Ray(const Vector3& origin, const Vector3& direction)
        : origin(origin), direction(direction) {}

    // Retorna o ponto no raio para um determinado valor de t (parâmetro)
    Vector3 pointAtParameter(float t) const {
        return origin + direction * t;
    }
};

#endif // RAY_H 