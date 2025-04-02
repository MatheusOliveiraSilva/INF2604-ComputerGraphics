#ifndef BOX_H
#define BOX_H

#include "Primitive.h"
#include "../material/Material.h"
#include <memory>

class Box : public Primitive {
private:
    Vector3D min;  // Vértice mínimo (canto inferior esquerdo traseiro)
    Vector3D max;  // Vértice máximo (canto superior direito frontal)
    std::shared_ptr<Material> material;

public:
    Box() = default;
    
    Box(const Vector3D& min, const Vector3D& max, std::shared_ptr<Material> material)
        : min(min), max(max), material(material) {}
    
    // Getters
    const Vector3D& getMin() const { return min; }
    const Vector3D& getMax() const { return max; }
    std::shared_ptr<Material> getMaterial() const { return material; }
    
    // Implementação de hit
    virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
};

#endif // BOX_H 