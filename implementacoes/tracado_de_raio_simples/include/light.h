#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

class Light {
public:
    Point3 position;    // Posição da luz (para luz pontual)
    Color color;        // Cor/intensidade da luz
    double intensity;   // Intensidade da luz

    Light()
        : position(0, 5, 0), color(1, 1, 1), intensity(1.0) {}

    Light(const Point3& pos, const Color& col, double intens)
        : position(pos), color(col), intensity(intens) {}

    // Calcula a direção da luz a partir de um ponto
    Vec3 direction_from(const Point3& hit_point) const {
        return (position - hit_point).normalized();
    }

    // Calcula a distância do ponto à luz
    double distance_from(const Point3& hit_point) const {
        return (position - hit_point).length();
    }
};

#endif // LIGHT_H 