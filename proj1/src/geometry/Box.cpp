#include "Box.h"
#include <limits>
#include <algorithm>

bool Box::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    double tmin = -std::numeric_limits<double>::infinity();
    double tmax = std::numeric_limits<double>::infinity();
    
    // Para cada eixo (x, y, z)
    for (int a = 0; a < 3; a++) {
        double invD;
        double coord_orig, min_coord, max_coord;
        
        // Selecionar o componente correto baseado no eixo
        if (a == 0) {
            invD = 1.0 / ray.direction().x;
            coord_orig = ray.origin().x;
            min_coord = min_point.x;
            max_coord = max_point.x;
        } else if (a == 1) {
            invD = 1.0 / ray.direction().y;
            coord_orig = ray.origin().y;
            min_coord = min_point.y;
            max_coord = max_point.y;
        } else {
            invD = 1.0 / ray.direction().z;
            coord_orig = ray.origin().z;
            min_coord = min_point.z;
            max_coord = max_point.z;
        }
        
        double t0 = (min_coord - coord_orig) * invD;
        double t1 = (max_coord - coord_orig) * invD;
        
        // Garantir que t0 é a interseção "entrada" e t1 é a "saída"
        if (invD < 0.0) {
            std::swap(t0, t1);
        }
        
        // Atualizar intervalos
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;
        
        if (tmax <= tmin) {
            return false;  // Raio não atinge a caixa
        }
    }
    
    // Verificar se a interseção está dentro do intervalo válido
    if (tmin < t_min || tmin > t_max) {
        return false;
    }
    
    rec.t = tmin;
    rec.point = ray.at(tmin);
    
    // Determinar qual face foi atingida para calcular a normal
    Vector3 outward_normal;
    double epsilon = 1e-8;
    
    Point3 centered = rec.point - (min_point + max_point) / 2.0;
    double dx = std::abs(centered.x) / (max_point.x - min_point.x);
    double dy = std::abs(centered.y) / (max_point.y - min_point.y);
    double dz = std::abs(centered.z) / (max_point.z - min_point.z);
    
    if (dx > dy && dx > dz) {
        outward_normal = Vector3(centered.x > 0 ? 1 : -1, 0, 0);
    } else if (dy > dz) {
        outward_normal = Vector3(0, centered.y > 0 ? 1 : -1, 0);
    } else {
        outward_normal = Vector3(0, 0, centered.z > 0 ? 1 : -1);
    }
    
    rec.set_face_normal(ray, outward_normal);
    rec.material = material;
    
    return true;
} 