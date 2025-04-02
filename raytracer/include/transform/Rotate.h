#ifndef ROTATE_H
#define ROTATE_H

#include "Transform.h"
#include <cmath>

// Rotação de objetos em torno de um eixo arbitrário
class Rotate : public Transform {
public:
    float angle;         // Ângulo de rotação em graus
    Vector3 axis;        // Eixo de rotação
    Vector3 rotation[3]; // Matriz de rotação
    Vector3 invRotation[3]; // Matriz de rotação inversa
    
    Rotate(Primitive* object, float angle, float x, float y, float z)
        : Transform(object), angle(angle), axis(normalize(Vector3(x, y, z))) {
        buildRotationMatrix();
    }
    
    Rotate(Primitive* object, float angle, const Vector3& axis)
        : Transform(object), angle(angle), axis(normalize(axis)) {
        buildRotationMatrix();
    }
    
    // Implementação do método hit para objetos rotacionados
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override {
        // Transformação inversa do raio (aplicar rotação inversa)
        Vector3 originRotated = applyInverseRotation(ray.origin);
        Vector3 directionRotated = applyInverseRotation(ray.direction);
        Ray rotatedRay(originRotated, directionRotated);
        
        // Verificar interseção com o objeto
        if (!object->hit(rotatedRay, tMin, tMax, record))
            return false;
        
        // Transformar o ponto e a normal de volta ao espaço original
        record.point = applyRotation(record.point);
        record.normal = normalize(applyRotation(record.normal));
        
        return true;
    }
    
private:
    // Constrói as matrizes de rotação e rotação inversa
    void buildRotationMatrix() {
        // Converter ângulo para radianos
        float radians = angle * M_PI / 180.0f;
        float cosTheta = cos(radians);
        float sinTheta = sin(radians);
        float oneMinusCos = 1.0f - cosTheta;
        
        // Construir matriz de rotação usando a fórmula do eixo-ângulo (Rodrigues)
        // Primeira linha
        rotation[0].x = cosTheta + axis.x * axis.x * oneMinusCos;
        rotation[0].y = axis.x * axis.y * oneMinusCos - axis.z * sinTheta;
        rotation[0].z = axis.x * axis.z * oneMinusCos + axis.y * sinTheta;
        
        // Segunda linha
        rotation[1].x = axis.y * axis.x * oneMinusCos + axis.z * sinTheta;
        rotation[1].y = cosTheta + axis.y * axis.y * oneMinusCos;
        rotation[1].z = axis.y * axis.z * oneMinusCos - axis.x * sinTheta;
        
        // Terceira linha
        rotation[2].x = axis.z * axis.x * oneMinusCos - axis.y * sinTheta;
        rotation[2].y = axis.z * axis.y * oneMinusCos + axis.x * sinTheta;
        rotation[2].z = cosTheta + axis.z * axis.z * oneMinusCos;
        
        // A matriz de rotação inversa é a transposta da matriz de rotação
        invRotation[0].x = rotation[0].x;
        invRotation[0].y = rotation[1].x;
        invRotation[0].z = rotation[2].x;
        
        invRotation[1].x = rotation[0].y;
        invRotation[1].y = rotation[1].y;
        invRotation[1].z = rotation[2].y;
        
        invRotation[2].x = rotation[0].z;
        invRotation[2].y = rotation[1].z;
        invRotation[2].z = rotation[2].z;
    }
    
    // Aplica a rotação a um vetor
    Vector3 applyRotation(const Vector3& v) const {
        return Vector3(
            dot(rotation[0], v),
            dot(rotation[1], v),
            dot(rotation[2], v)
        );
    }
    
    // Aplica a rotação inversa a um vetor
    Vector3 applyInverseRotation(const Vector3& v) const {
        return Vector3(
            dot(invRotation[0], v),
            dot(invRotation[1], v),
            dot(invRotation[2], v)
        );
    }
};

#endif // ROTATE_H 