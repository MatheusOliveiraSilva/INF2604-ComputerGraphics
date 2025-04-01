#include "Triangle.h"
#include <limits>

// Implementação do algoritmo de Möller-Trumbore para interseção raio-triângulo
bool Triangle::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    // Direção do raio
    const Vector3& dir = ray.direction();
    
    // Vetor perpendicular à direção do raio e edge2
    Vector3 pvec = cross(dir, edge2);
    
    // Calcular determinante
    double det = dot(edge1, pvec);
    
    // Se o determinante estiver próximo de zero, o raio está paralelo ao triângulo
    // Também implementa culling de face (apenas interseções pela frente)
    if (det < 1e-8) return false;
    
    double inv_det = 1.0 / det;
    
    // Calcular distância de v0 à origem do raio
    Vector3 tvec = ray.origin() - v0;
    
    // Calcular coordenada baricêntrica u
    double u = dot(tvec, pvec) * inv_det;
    
    // Verificar se está fora do triângulo
    if (u < 0.0 || u > 1.0) return false;
    
    // Calcular coordenada baricêntrica v
    Vector3 qvec = cross(tvec, edge1);
    double v = dot(dir, qvec) * inv_det;
    
    // Verificar se está fora do triângulo
    if (v < 0.0 || u + v > 1.0) return false;
    
    // Calcular t, distância ao longo do raio
    double t = dot(edge2, qvec) * inv_det;
    
    // Verificar limites de t
    if (t < t_min || t > t_max) return false;
    
    // Temos uma interseção válida, configurar registro
    rec.t = t;
    rec.point = ray.at(t);
    rec.set_face_normal(ray, normal);
    rec.material = material;
    
    return true;
} 