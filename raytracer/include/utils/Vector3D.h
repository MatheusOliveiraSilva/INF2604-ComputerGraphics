#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <iostream>

class Vector3D {
public:
    // Componentes
    double x, y, z;

    // Construtores
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
    Vector3D(const Vector3D& v) : x(v.x), y(v.y), z(v.z) {}

    // Operadores
    Vector3D operator+(const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D operator-(const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D operator/(double scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    Vector3D& operator+=(const Vector3D& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3D& operator-=(const Vector3D& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3D& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3D& operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // Produto escalar (dot product)
    double dot(const Vector3D& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // Produto vetorial (cross product)
    Vector3D cross(const Vector3D& v) const {
        return Vector3D(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    // Norma (magnitude) do vetor
    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Quadrado da norma
    double lengthSquared() const {
        return x * x + y * y + z * z;
    }

    // Normalização
    Vector3D normalized() const {
        double len = length();
        if (len > 0) {
            return *this / len;
        }
        return *this;
    }

    void normalize() {
        double len = length();
        if (len > 0) {
            *this /= len;
        }
    }
};

// Operador de multiplicação escalar à esquerda
inline Vector3D operator*(double scalar, const Vector3D& v) {
    return v * scalar;
}

// Operador de saída (para debug)
inline std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

#endif // VECTOR3D_H 