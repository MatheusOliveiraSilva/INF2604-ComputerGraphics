#include "../../include/geometry/Sphere.h"

bool Sphere::hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
    // Vector do centro da esfera para a origem do raio
    Vector3D oc = ray.origin - center;
    
    // Coeficientes da equação quadrática
    double a = ray.direction.lengthSquared();
    double half_b = oc.dot(ray.direction);
    double c = oc.lengthSquared() - radius * radius;
    
    // Discriminante
    double discriminant = half_b * half_b - a * c;
    
    // Se discriminante < 0, não há interseção
    if (discriminant < 0) {
        return false;
    }
    
    // Calcula a raiz mais próxima dentro do intervalo [tMin, tMax]
    double sqrtd = sqrt(discriminant);
    double root = (-half_b - sqrtd) / a;
    
    if (root < tMin || root > tMax) {
        root = (-half_b + sqrtd) / a;
        if (root < tMin || root > tMax) {
            return false;
        }
    }
    
    // Preenche o registro de interseção
    record.t = root;
    record.point = ray.pointAtParameter(record.t);
    Vector3D outwardNormal = (record.point - center) / radius;  // Normal apontando para fora
    record.setFaceNormal(ray.direction, outwardNormal);
    record.material = material;
    
    return true;
} 