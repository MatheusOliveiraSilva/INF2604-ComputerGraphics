#include "../../include/geometry/Box.h"
#include <algorithm>

bool Box::hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
    double tNear = tMin;
    double tFar = tMax;
    
    // Para cada eixo (x, y, z)
    for (int i = 0; i < 3; i++) {
        double minComponent, maxComponent, originComponent, dirComponent;
        
        // Seleciona o componente atual (x, y ou z)
        switch (i) {
            case 0:  // Eixo X
                minComponent = min.x;
                maxComponent = max.x;
                originComponent = ray.origin.x;
                dirComponent = ray.direction.x;
                break;
            case 1:  // Eixo Y
                minComponent = min.y;
                maxComponent = max.y;
                originComponent = ray.origin.y;
                dirComponent = ray.direction.y;
                break;
            case 2:  // Eixo Z
                minComponent = min.z;
                maxComponent = max.z;
                originComponent = ray.origin.z;
                dirComponent = ray.direction.z;
                break;
        }
        
        // Evita divisão por zero
        if (std::abs(dirComponent) < 1e-8) {
            // Se a origem está fora da caixa, não há interseção
            if (originComponent < minComponent || originComponent > maxComponent) {
                return false;
            }
        } else {
            // Calcula interseções com planos paralelos ao eixo atual
            double t1 = (minComponent - originComponent) / dirComponent;
            double t2 = (maxComponent - originComponent) / dirComponent;
            
            // Garante que t1 seja a interseção mais próxima
            if (t1 > t2) std::swap(t1, t2);
            
            // Atualiza tNear e tFar
            tNear = std::max(tNear, t1);
            tFar = std::min(tFar, t2);
            
            // Se não há interseção
            if (tNear > tFar) {
                return false;
            }
        }
    }
    
    // Se tNear > tMax ou tFar < tMin, não há interseção no intervalo válido
    if (tNear > tMax || tFar < tMin) {
        return false;
    }
    
    // Registra a interseção
    record.t = tNear;
    record.point = ray.pointAtParameter(tNear);
    
    // Determina a normal baseada em qual face foi atingida
    Vector3D normal;
    
    // Calcula o ponto relativo ao centro da caixa
    Vector3D center = (min + max) * 0.5;
    Vector3D relativePoint = record.point - center;
    Vector3D extents = max - min;
    
    // Encontra qual face foi atingida comparando a posição relativa com as dimensões
    double epsilon = 1e-5;
    if (std::abs(relativePoint.x - extents.x/2) < epsilon) {
        normal = Vector3D(1, 0, 0);
    } else if (std::abs(relativePoint.x + extents.x/2) < epsilon) {
        normal = Vector3D(-1, 0, 0);
    } else if (std::abs(relativePoint.y - extents.y/2) < epsilon) {
        normal = Vector3D(0, 1, 0);
    } else if (std::abs(relativePoint.y + extents.y/2) < epsilon) {
        normal = Vector3D(0, -1, 0);
    } else if (std::abs(relativePoint.z - extents.z/2) < epsilon) {
        normal = Vector3D(0, 0, 1);
    } else {
        normal = Vector3D(0, 0, -1);
    }
    
    record.setFaceNormal(ray.direction, normal);
    record.material = material;
    
    return true;
} 