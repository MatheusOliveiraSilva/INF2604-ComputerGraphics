#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../geometry/Primitive.h"

// Interface para transformações geométricas
class Transform : public Primitive {
public:
    Primitive* object;  // Objeto a ser transformado
    
    Transform(Primitive* object) : object(object) {}
    virtual ~Transform() = default;
    
    // A implementação de hit deve ser fornecida pelas subclasses
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override = 0;
};

#endif // TRANSFORM_H 