#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include "../core/Vector3.h"

class Transform {
public:
    // Matriz de transformação 4x4 (guardada como array unidimensional em ordem de coluna)
    double matrix[16];
    double inverse[16];
    
    // Construtor padrão (matriz identidade)
    Transform() {
        identity();
    }
    
    // Inicializa a matriz como identidade
    void identity() {
        for (int i = 0; i < 16; i++) {
            matrix[i] = (i % 5 == 0) ? 1.0 : 0.0;
            inverse[i] = (i % 5 == 0) ? 1.0 : 0.0;
        }
    }
    
    // Translação
    static Transform translate(const Vector3& v) {
        Transform t;
        // Última coluna
        t.matrix[3] = v.x;
        t.matrix[7] = v.y;
        t.matrix[11] = v.z;
        
        // Inversa (translação negativa)
        t.inverse[3] = -v.x;
        t.inverse[7] = -v.y;
        t.inverse[11] = -v.z;
        
        return t;
    }
    
    // Escala
    static Transform scale(const Vector3& s) {
        Transform t;
        t.matrix[0] = s.x;
        t.matrix[5] = s.y;
        t.matrix[10] = s.z;
        
        // Inversa (reciprocos)
        t.inverse[0] = 1.0 / s.x;
        t.inverse[5] = 1.0 / s.y;
        t.inverse[10] = 1.0 / s.z;
        
        return t;
    }
    
    // Rotação em X
    static Transform rotate_x(double angle) {
        Transform t;
        double sin_a = std::sin(angle);
        double cos_a = std::cos(angle);
        
        t.matrix[5] = cos_a;
        t.matrix[6] = -sin_a;
        t.matrix[9] = sin_a;
        t.matrix[10] = cos_a;
        
        // Inversa (transposta)
        t.inverse[5] = cos_a;
        t.inverse[6] = sin_a;
        t.inverse[9] = -sin_a;
        t.inverse[10] = cos_a;
        
        return t;
    }
    
    // Rotação em Y
    static Transform rotate_y(double angle) {
        Transform t;
        double sin_a = std::sin(angle);
        double cos_a = std::cos(angle);
        
        t.matrix[0] = cos_a;
        t.matrix[2] = sin_a;
        t.matrix[8] = -sin_a;
        t.matrix[10] = cos_a;
        
        // Inversa (transposta)
        t.inverse[0] = cos_a;
        t.inverse[2] = -sin_a;
        t.inverse[8] = sin_a;
        t.inverse[10] = cos_a;
        
        return t;
    }
    
    // Rotação em Z
    static Transform rotate_z(double angle) {
        Transform t;
        double sin_a = std::sin(angle);
        double cos_a = std::cos(angle);
        
        t.matrix[0] = cos_a;
        t.matrix[1] = -sin_a;
        t.matrix[4] = sin_a;
        t.matrix[5] = cos_a;
        
        // Inversa (transposta)
        t.inverse[0] = cos_a;
        t.inverse[1] = sin_a;
        t.inverse[4] = -sin_a;
        t.inverse[5] = cos_a;
        
        return t;
    }
    
    // Composição de transformações
    Transform operator*(const Transform& t) const {
        Transform result;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.matrix[i * 4 + j] = 0.0;
                for (int k = 0; k < 4; k++) {
                    result.matrix[i * 4 + j] += matrix[k * 4 + j] * t.matrix[i * 4 + k];
                }
            }
        }
        
        // Calcular a inversa (t.inverse * inverse)
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.inverse[i * 4 + j] = 0.0;
                for (int k = 0; k < 4; k++) {
                    result.inverse[i * 4 + j] += t.inverse[k * 4 + j] * inverse[i * 4 + k];
                }
            }
        }
        
        return result;
    }
    
    // Aplicar a transformação a um ponto
    Point3 apply_point(const Point3& p) const {
        double x = p.x * matrix[0] + p.y * matrix[1] + p.z * matrix[2] + matrix[3];
        double y = p.x * matrix[4] + p.y * matrix[5] + p.z * matrix[6] + matrix[7];
        double z = p.x * matrix[8] + p.y * matrix[9] + p.z * matrix[10] + matrix[11];
        double w = p.x * matrix[12] + p.y * matrix[13] + p.z * matrix[14] + matrix[15];
        
        if (w == 1.0) return Point3(x, y, z);
        return Point3(x/w, y/w, z/w);
    }
    
    // Aplicar a transformação a um vetor (sem translação)
    Vector3 apply_vector(const Vector3& v) const {
        return Vector3(
            v.x * matrix[0] + v.y * matrix[1] + v.z * matrix[2],
            v.x * matrix[4] + v.y * matrix[5] + v.z * matrix[6],
            v.x * matrix[8] + v.y * matrix[9] + v.z * matrix[10]
        );
    }
    
    // Aplicar a transformação a uma normal (usando a inversa transposta)
    Vector3 apply_normal(const Vector3& n) const {
        return Vector3(
            n.x * inverse[0] + n.y * inverse[4] + n.z * inverse[8],
            n.x * inverse[1] + n.y * inverse[5] + n.z * inverse[9],
            n.x * inverse[2] + n.y * inverse[6] + n.z * inverse[10]
        );
    }
    
    // Aplicar a transformação a um raio
    Ray apply_ray(const Ray& ray) const {
        return Ray(
            apply_point(ray.origin()),
            apply_vector(ray.direction())
        );
    }
};

#endif 