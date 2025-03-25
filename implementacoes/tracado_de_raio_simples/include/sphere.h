#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class Sphere : public Object {
public:
    Point3 center;
    double radius;

    Sphere() : center(0, 0, 0), radius(1.0) {
        material = std::make_shared<Material>();
    }

    Sphere(const Point3& c, double r, std::shared_ptr<Material> m)
        : center(c), radius(r) {
        material = m;
    }

    // Implementação da interseção raio-esfera
    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override {
        Vec3 oc = ray.origin - center;
        double a = ray.direction.length_squared();
        double half_b = dot(oc, ray.direction);
        double c = oc.length_squared() - radius * radius;
        
        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;
        
        double sqrtd = sqrt(discriminant);

        // Encontra a raiz mais próxima no intervalo aceitável [t_min, t_max]
        double root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        rec.t = root;
        rec.point = ray.at(rec.t);
        Vec3 outward_normal = (rec.point - center) / radius;
        rec.set_face_normal(ray, outward_normal);
        rec.material = material;

        return true;
    }
};

#endif // SPHERE_H 