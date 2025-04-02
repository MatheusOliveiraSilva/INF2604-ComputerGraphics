#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../core/Ray.h"
#include "../core/HitRecord.h"

// Interface para objetos primitivos
class Primitive {
public:
    virtual ~Primitive() = default;
    
    // Verifica se o raio intersecta a primitiva
    // tMin e tMax definem intervalo de intersecção válido
    virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};

#endif // PRIMITIVE_H 