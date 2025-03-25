#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
public:
    Point3 origin;
    Vec3 direction;

    Ray() {}
    Ray(const Point3& origin, const Vec3& direction)
        : origin(origin), direction(direction) {}

    // Retorna o ponto ao longo do raio para um determinado valor de t
    Point3 at(double t) const {
        return origin + t * direction;
    }
};

#endif // RAY_H 