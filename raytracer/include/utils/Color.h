#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <iostream>

class Color {
public:
    double r, g, b;  // Componentes R, G, B (0.0 - 1.0)

    // Construtores
    Color() : r(0), g(0), b(0) {}
    Color(double r, double g, double b) : r(r), g(g), b(b) {}
    Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}

    // Operadores
    Color operator+(const Color& c) const {
        return Color(r + c.r, g + c.g, b + c.b);
    }

    Color operator-(const Color& c) const {
        return Color(r - c.r, g - c.g, b - c.b);
    }

    Color operator*(double scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    Color operator*(const Color& c) const {
        return Color(r * c.r, g * c.g, b * c.b);
    }

    Color& operator+=(const Color& c) {
        r += c.r;
        g += c.g;
        b += c.b;
        return *this;
    }

    // Limita os valores entre 0 e 1
    void clamp() {
        r = std::clamp(r, 0.0, 1.0);
        g = std::clamp(g, 0.0, 1.0);
        b = std::clamp(b, 0.0, 1.0);
    }

    // Converte para inteiros (0-255)
    int toR8() const { return static_cast<int>(r * 255.999); }
    int toG8() const { return static_cast<int>(g * 255.999); }
    int toB8() const { return static_cast<int>(b * 255.999); }
};

// Operador escalar à esquerda
inline Color operator*(double scalar, const Color& c) {
    return c * scalar;
}

// Operador de saída
inline std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << c.toR8() << " " << c.toG8() << " " << c.toB8();
    return os;
}

// Cores predefinidas
namespace Colors {
    const Color BLACK(0, 0, 0);
    const Color WHITE(1, 1, 1);
    const Color RED(1, 0, 0);
    const Color GREEN(0, 1, 0);
    const Color BLUE(0, 0, 1);
    const Color YELLOW(1, 1, 0);
    const Color CYAN(0, 1, 1);
    const Color MAGENTA(1, 0, 1);
    const Color GRAY(0.5, 0.5, 0.5);
}

#endif // COLOR_H 