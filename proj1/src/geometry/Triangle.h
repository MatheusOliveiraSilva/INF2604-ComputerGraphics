#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "../core/Vector3.h"

class Triangle : public Object {
public:
    Triangle() {}
    Triangle(const Point3& v0, const Point3& v1, const Point3& v2, Material* material)
        : v0(v0), v1(v1), v2(v2), material(material) {
        // Calcular normal do triângulo (assume-se que está no sentido anti-horário)
        edge1 = v1 - v0;
        edge2 = v2 - v0;
        normal = normalize(cross(edge1, edge2));
    }

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;

private:
    Point3 v0, v1, v2;          // Vértices do triângulo
    Vector3 edge1, edge2;        // Arestas pré-calculadas
    Vector3 normal;              // Normal pré-calculada
    Material* material;
};

#endif 