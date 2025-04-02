#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"
#include "../material/Material.h"
#include <memory>

class Sphere : public Primitive {
private:
    Vector3D center;
    double radius;
    std::shared_ptr<Material> material;

public:
    Sphere() = default;
    
    Sphere(const Vector3D& center, double radius, std::shared_ptr<Material> material)
        : center(center), radius(radius), material(material) {}
    
    // Getters
    const Vector3D& getCenter() const { return center; }
    double getRadius() const { return radius; }
    std::shared_ptr<Material> getMaterial() const { return material; }
    
    // Implementação de hit
    virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
};

#endif // SPHERE_H 