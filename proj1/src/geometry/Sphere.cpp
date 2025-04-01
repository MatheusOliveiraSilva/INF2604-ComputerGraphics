#include "Sphere.h"

bool Sphere::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    Vector3 oc = ray.origin() - center;
    auto a = ray.direction().length_squared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.length_squared() - radius * radius;
    
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Encontrar a raiz mais próxima que está no intervalo aceitável
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.point = ray.at(rec.t);
    Vector3 outward_normal = (rec.point - center) / radius;
    rec.set_face_normal(ray, outward_normal);
    rec.material = material;

    return true;
} 