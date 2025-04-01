#ifndef OBJECT_H
#define OBJECT_H

#include "../core/Ray.h"
#include "../core/Vector3.h"

class Material;

struct HitRecord {
    Point3 point;
    Vector3 normal;
    double t;
    bool front_face;
    Material* material = nullptr;

    inline void set_face_normal(const Ray& ray, const Vector3& outward_normal) {
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Object {
public:
    virtual ~Object() = default;
    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif 