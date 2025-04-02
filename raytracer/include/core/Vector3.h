#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>
#include <stdexcept>

class Vector3 {
public:
    float x, y, z;

    // Construtores
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

    // Operadores
    Vector3& operator=(const Vector3& v) {
        x = v.x; y = v.y; z = v.z;
        return *this;
    }
    
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    
    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }
    
    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }
    
    Vector3 operator*(float t) const {
        return Vector3(x * t, y * t, z * t);
    }
    
    Vector3 operator/(float t) const {
        float invT = 1.0f / t;
        return Vector3(x * invT, y * invT, z * invT);
    }
    
    Vector3& operator+=(const Vector3& v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    
    Vector3& operator-=(const Vector3& v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    
    Vector3& operator*=(float t) {
        x *= t; y *= t; z *= t;
        return *this;
    }
    
    Vector3& operator/=(float t) {
        float invT = 1.0f / t;
        x *= invT; y *= invT; z *= invT;
        return *this;
    }
    
    // Acesso por índice
    float operator[](int i) const {
        switch(i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::out_of_range("Vector3 index out of range");
        }
    }
    
    float& operator[](int i) {
        switch(i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::out_of_range("Vector3 index out of range");
        }
    }
    
    // Métodos de utilidade
    float length() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    float squaredLength() const {
        return x*x + y*y + z*z;
    }
    
    void normalize() {
        float len = length();
        if (len > 0) {
            x /= len; y /= len; z /= len;
        }
    }
    
    Vector3 normalized() const {
        float len = length();
        if (len > 0) {
            return Vector3(x/len, y/len, z/len);
        }
        return *this;
    }
    
    // Produto escalar
    float dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    
    // Produto vetorial
    Vector3 cross(const Vector3& v) const {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }
};

// Operadores externos
inline Vector3 operator*(float t, const Vector3& v) {
    return v * t;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

// Funções de utilidade para vetores
inline float dot(const Vector3& a, const Vector3& b) {
    return a.dot(b);
}

inline Vector3 cross(const Vector3& a, const Vector3& b) {
    return a.cross(b);
}

inline Vector3 normalize(const Vector3& v) {
    return v.normalized();
}

#endif // VECTOR3_H 