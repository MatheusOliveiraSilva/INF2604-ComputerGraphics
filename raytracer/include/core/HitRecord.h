#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "../utils/Vector3D.h"
#include <memory>

// Forward declaration
class Material;

// Estrutura para armazenar informações sobre uma intersecção raio-objeto
struct HitRecord {
    double t;             // Parâmetro do raio no ponto de intersecção
    Vector3D point;       // Ponto de intersecção
    Vector3D normal;      // Normal à superfície no ponto de intersecção
    std::shared_ptr<Material> material;   // Material do objeto no ponto de intersecção
    bool frontFace;       // Se a normal está voltada para a origem do raio
    
    // Define a normal para garantir que sempre aponte contra o raio
    inline void setFaceNormal(const Vector3D& rayDirection, const Vector3D& outwardNormal) {
        frontFace = rayDirection.dot(outwardNormal) < 0;
        normal = frontFace ? outwardNormal : outwardNormal * -1.0;
    }
};

#endif // HIT_RECORD_H 