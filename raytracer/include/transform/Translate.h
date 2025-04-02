#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "Transform.h"

// Translação de objetos
class Translate : public Transform {
public:
    Vector3 offset;  // Vetor de translação
    
    Translate(Primitive* object, float x, float y, float z)
        : Transform(object), offset(x, y, z) {}
    
    Translate(Primitive* object, const Vector3& offset)
        : Transform(object), offset(offset) {}
    
    // Implementação do método hit para objetos transladados
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override {
        // Transformação inversa do raio (mover na direção oposta à translação)
        Ray movedRay(ray.origin - offset, ray.direction);
        
        // Verificar interseção com o objeto transformado
        if (!object->hit(movedRay, tMin, tMax, record))
            return false;
        
        // Ajustar o ponto de interseção para o espaço original
        record.point += offset;
        
        return true;
    }
};

#endif // TRANSLATE_H

 