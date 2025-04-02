#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../core/Ray.h"

// Declaração antecipada de Material
class Material;

// Estrutura para armazenar informações sobre a interseção
struct HitRecord {
    float t;               // Parâmetro do raio no ponto de interseção
    Vector3 point;         // Ponto de interseção
    Vector3 normal;        // Normal à superfície no ponto de interseção
    Material* material;    // Material da superfície
    bool frontFace;        // Indica se a interseção foi pela face frontal

    // Define a normal para que sempre aponte contra o raio
    inline void setFaceNormal(const Ray& ray, const Vector3& outwardNormal) {
        frontFace = dot(ray.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

// Interface para todas as primitivas geométricas
class Primitive {
public:
    virtual ~Primitive() = default;

    // Verifica se há interseção entre o raio e a primitiva
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const = 0;
};

#endif // PRIMITIVE_H 