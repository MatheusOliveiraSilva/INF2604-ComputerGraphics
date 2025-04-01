#ifndef BOX_H
#define BOX_H

#include "Object.h"
#include "../core/Vector3.h"

class Box : public Object {
public:
    Box() {}
    Box(const Point3& min, const Point3& max, Material* material)
        : min_point(min), max_point(max), material(material) {}

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;

private:
    Point3 min_point;
    Point3 max_point;
    Material* material;
};

#endif 