#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include "Vector3.h"

class Color : public Vector3 {
public:
    Color() : Vector3(0, 0, 0) {}
    Color(double r, double g, double b) : Vector3(r, g, b) {}
    Color(const Vector3& v) : Vector3(v) {}

    double r() const { return x; }
    double g() const { return y; }
    double b() const { return z; }

    void write_color(std::ostream& out, int samples_per_pixel = 1) const {
        // Dividir a cor pelo número de amostras e realizar correção gamma (gamma=2.0)
        auto scale = 1.0 / samples_per_pixel;
        auto r = std::sqrt(scale * x);
        auto g = std::sqrt(scale * y);
        auto b = std::sqrt(scale * z);

        // Escrever os valores de componentes traduzidos [0,255]
        out << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << '\n';
    }
};

#endif 