#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere : public Primitive {
public:
    Vector3 center;
    float radius;
    Material* material;

    // Construtores
    Sphere() : center(0, 0, 0), radius(1), material(nullptr) {}
    
    Sphere(const Vector3& center, float radius, Material* material)
        : center(center), radius(radius), material(material) {}

    // Implementação da função hit para verificar interseção com um raio
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override {
        Vector3 oc = ray.origin - center;
        float a = ray.direction.squaredLength();
        float halfB = dot(oc, ray.direction);
        float c = oc.squaredLength() - radius * radius;
        
        float discriminant = halfB * halfB - a * c;
        if (discriminant < 0) return false;
        
        float sqrtd = sqrt(discriminant);
        
        // Encontrar a raiz mais próxima dentro do intervalo aceitável
        float root = (-halfB - sqrtd) / a;
        if (root < tMin || tMax < root) {
            root = (-halfB + sqrtd) / a;
            if (root < tMin || tMax < root)
                return false;
        }
        
        // Preencher o registro de interseção
        record.t = root;
        record.point = ray.pointAtParameter(root);
        Vector3 outwardNormal = (record.point - center) / radius;
        record.setFaceNormal(ray, outwardNormal);
        record.material = material;
        
        return true;
    }
};

#endif // SPHERE_H 