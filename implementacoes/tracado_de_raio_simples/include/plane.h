#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object {
public:
    Point3 point;  // Um ponto no plano
    Vec3 normal;   // Normal do plano (normalizada)

    Plane() : point(0, 0, 0), normal(0, 1, 0) {
        material = std::make_shared<Material>();
    }

    Plane(const Point3& p, const Vec3& n, std::shared_ptr<Material> m)
        : point(p), normal(n.normalized()) {
        material = m;
    }

    // Implementação da interseção raio-plano
    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override {
        double denom = dot(normal, ray.direction);

        // Raio paralelo ao plano
        if (fabs(denom) < 1e-8) return false;

        // Calcula o valor de t na interseção
        double t = dot(point - ray.origin, normal) / denom;

        // Verifica se a interseção está no intervalo válido
        if (t < t_min || t > t_max) return false;

        // Preenche o registro de interseção
        rec.t = t;
        rec.point = ray.at(t);
        rec.set_face_normal(ray, normal);
        rec.material = material;

        return true;
    }
};

#endif // PLANE_H 