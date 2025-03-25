#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

class Material {
public:
    Color ambient;       // Componente ambiente do material
    Color diffuse;       // Componente difusa do material
    Color specular;      // Componente especular do material
    double shininess;    // Expoente da reflexão especular

    Material()
        : ambient(0.1, 0.1, 0.1), diffuse(0.7, 0.7, 0.7), specular(1.0, 1.0, 1.0), shininess(32.0) {}
    
    Material(const Color& a, const Color& d, const Color& s, double sh)
        : ambient(a), diffuse(d), specular(s), shininess(sh) {}
};

#endif // MATERIAL_H 