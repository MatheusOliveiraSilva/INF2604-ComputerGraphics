#ifndef LIGHT_H
#define LIGHT_H

#include "../utils/Vector3D.h"
#include "../utils/Color.h"

// Interface para fontes de luz
class Light {
public:
    virtual ~Light() = default;
    
    // Retorna a direção da luz a partir de um ponto
    virtual Vector3D getDirection(const Vector3D& point) const = 0;
    
    // Retorna a intensidade da luz em um ponto
    virtual Color getIntensity(const Vector3D& point) const = 0;
    
    // Retorna a posição da luz (para cálculo de sombras)
    virtual Vector3D getPosition() const = 0;
    
    // Retorna a distância do ponto até a luz
    virtual double getDistance(const Vector3D& point) const = 0;
};

// Implementação de luz pontual
class PointLight : public Light {
private:
    Vector3D position;
    Color intensity;

public:
    PointLight(const Vector3D& position, const Color& intensity)
        : position(position), intensity(intensity) {}
    
    // Implementações
    Vector3D getDirection(const Vector3D& point) const override {
        return (position - point).normalized();
    }
    
    Color getIntensity(const Vector3D& point) const override {
        // Modelo de atenuação simples: intensidade diminui com o quadrado da distância
        double distance = (position - point).length();
        double attenuation = 1.0 / (1.0 + 0.01 * distance + 0.001 * distance * distance);
        return intensity * attenuation;
    }
    
    Vector3D getPosition() const override {
        return position;
    }
    
    double getDistance(const Vector3D& point) const override {
        return (position - point).length();
    }
};

#endif // LIGHT_H 