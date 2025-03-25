#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include "material.h"
#include <memory>

// Estrutura para armazenar informações sobre uma interseção
struct HitRecord {
    Point3 point;        // Ponto de interseção
    Vec3 normal;         // Normal no ponto de interseção (normalizada)
    double t;            // Parâmetro t do raio
    bool front_face;     // Flag para indicar se a normal aponta para fora do objeto
    std::shared_ptr<Material> material;  // Material do objeto atingido

    // Define a orientação da normal baseada na direção do raio
    inline void set_face_normal(const Ray& ray, const Vec3& outward_normal) {
        front_face = dot(ray.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

// Classe base para objetos da cena
class Object {
public:
    virtual ~Object() = default;

    // Método para testar interseção com um raio
    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const = 0;

    // Material do objeto
    std::shared_ptr<Material> material;
};

#endif // OBJECT_H 