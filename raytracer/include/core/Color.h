#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include "Vector3.h"

class Color {
public:
    float r, g, b;

    // Construtores
    Color() : r(0), g(0), b(0) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
    Color(const Vector3& v) : r(v.x), g(v.y), b(v.z) {}
    Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}

    // Operadores
    Color& operator=(const Color& c) {
        r = c.r; g = c.g; b = c.b;
        return *this;
    }

    Color operator+(const Color& c) const {
        return Color(r + c.r, g + c.g, b + c.b);
    }

    Color operator-(const Color& c) const {
        return Color(r - c.r, g - c.g, b - c.b);
    }

    Color operator*(float t) const {
        return Color(r * t, g * t, b * t);
    }

    Color operator*(const Color& c) const {
        return Color(r * c.r, g * c.g, b * c.b);
    }

    Color operator/(float t) const {
        float inv = 1.0f / t;
        return Color(r * inv, g * inv, b * inv);
    }

    Color& operator+=(const Color& c) {
        r += c.r; g += c.g; b += c.b;
        return *this;
    }

    Color& operator*=(float t) {
        r *= t; g *= t; b *= t;
        return *this;
    }

    Color& operator*=(const Color& c) {
        r *= c.r; g *= c.g; b *= c.b;
        return *this;
    }

    // Métodos de utilidade
    void clamp() {
        r = std::max(0.0f, std::min(1.0f, r));
        g = std::max(0.0f, std::min(1.0f, g));
        b = std::max(0.0f, std::min(1.0f, b));
    }

    Vector3 toVector3() const {
        return Vector3(r, g, b);
    }

    // Converte para inteiros de 0-255 para salvar em imagem
    unsigned char getR255() const { return static_cast<unsigned char>(255.99f * std::max(0.0f, std::min(1.0f, r))); }
    unsigned char getG255() const { return static_cast<unsigned char>(255.99f * std::max(0.0f, std::min(1.0f, g))); }
    unsigned char getB255() const { return static_cast<unsigned char>(255.99f * std::max(0.0f, std::min(1.0f, b))); }
};

// Operadores externos
inline Color operator*(float t, const Color& c) {
    return c * t;
}

#endif // COLOR_H 