#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3 {
public:
    double x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    
    Vector3& operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3& operator*=(double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vector3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return x*x + y*y + z*z;
    }

    bool near_zero() const {
        const auto s = 1e-8;
        return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
    }

    static Vector3 random(double min = 0.0, double max = 1.0);
};

// Funções utilitárias
inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vector3 operator+(const Vector3& u, const Vector3& v) {
    return Vector3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v) {
    return Vector3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v) {
    return Vector3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vector3 operator*(double t, const Vector3& v) {
    return Vector3(t * v.x, t * v.y, t * v.z);
}

inline Vector3 operator*(const Vector3& v, double t) {
    return t * v;
}

inline Vector3 operator/(Vector3 v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector3& u, const Vector3& v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline Vector3 cross(const Vector3& u, const Vector3& v) {
    return Vector3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

inline Vector3 normalize(Vector3 v) {
    return v / v.length();
}

using Point3 = Vector3;  // Para diferenciar pontos de vetores

#endif 