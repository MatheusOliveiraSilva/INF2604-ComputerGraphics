#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3 {
public:
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    // Operações básicas de vetores
    Vec3 operator-() const { return Vec3(-x, -y, -z); }
    
    Vec3& operator+=(const Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3& operator*=(const double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec3& operator/=(const double t) {
        return *this *= 1/t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return x*x + y*y + z*z;
    }

    // Método para normalizar o vetor
    Vec3 normalized() const {
        double len = length();
        return Vec3(x/len, y/len, z/len);
    }
};

// Funções auxiliares para operações com vetores
inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator*(double t, const Vec3& v) {
    return Vec3(t * v.x, t * v.y, t * v.z);
}

inline Vec3 operator*(const Vec3& v, double t) {
    return t * v;
}

inline Vec3 operator/(const Vec3& v, double t) {
    return (1.0/t) * v;
}

// Produto escalar
inline double dot(const Vec3& u, const Vec3& v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

// Produto vetorial
inline Vec3 cross(const Vec3& u, const Vec3& v) {
    return Vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

// Alias para vetores usados como cores
using Color = Vec3;

// Alias para vetores usados como pontos
using Point3 = Vec3;

#endif // VEC3_H 