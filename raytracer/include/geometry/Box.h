#ifndef BOX_H
#define BOX_H

#include "Primitive.h"

class Box : public Primitive {
public:
    Vector3 min;     // Ponto mínimo (canto inferior esquerdo posterior)
    Vector3 max;     // Ponto máximo (canto superior direito frontal)
    Material* material;

    // Construtores
    Box() : min(0, 0, 0), max(1, 1, 1), material(nullptr) {}
    
    Box(const Vector3& min, const Vector3& max, Material* material)
        : min(min), max(max), material(material) {}

    // Implementação da função hit para verificar interseção com um raio
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override {
        float t1, t2, tNear = tMin, tFar = tMax;
        Vector3 normal;
        int hitAxis = -1;
        
        // Verificar interseção com cada par de planos paralelos
        for (int i = 0; i < 3; i++) {
            float invD = 1.0f / ray.direction[i];
            t1 = (min[i] - ray.origin[i]) * invD;
            t2 = (max[i] - ray.origin[i]) * invD;
            
            // Garantir que t1 <= t2
            if (invD < 0.0f) std::swap(t1, t2);
            
            // Atualizar limites
            if (t1 > tNear) {
                tNear = t1;
                hitAxis = i;
            }
            if (t2 < tFar) tFar = t2;
            
            // Sem interseção
            if (tNear > tFar) return false;
        }
        
        // Verificar se a interseção está no intervalo válido
        if (tNear < tMin || tNear > tMax) return false;
        
        // Preencher o registro de interseção
        record.t = tNear;
        record.point = ray.pointAtParameter(tNear);
        
        // Calcular a normal baseada na face atingida
        normal = Vector3(0, 0, 0);
        float epsilon = 1e-6;
        
        if (hitAxis == 0) {
            normal.x = ray.direction.x < 0 ? 1 : -1;
        } else if (hitAxis == 1) {
            normal.y = ray.direction.y < 0 ? 1 : -1;
        } else if (hitAxis == 2) {
            normal.z = ray.direction.z < 0 ? 1 : -1;
        }
        
        record.setFaceNormal(ray, normal);
        record.material = material;
        
        return true;
    }
};

#endif // BOX_H 