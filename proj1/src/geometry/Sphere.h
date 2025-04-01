#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "../core/Vector3.h"

class Sphere : public Object {
public:
    Sphere() {}
    Sphere(Point3 center, double radius, Material* material)
        : center(center), radius(radius), material(material) {}

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;

private:
    Point3 center;
    double radius;
    Material* material;
};

#endif 