#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
    Vector3 position;    // Posição da luz
    Color intensity;     // Intensidade/cor da luz
    
    // Construtores
    PointLight() : position(0, 0, 0), intensity(1, 1, 1) {}
    
    PointLight(const Vector3& position, const Color& intensity)
        : position(position), intensity(intensity) {}
    
    // Implementação dos métodos da interface Light
    virtual Vector3 getDirection(const Vector3& point) const override {
        return normalize(position - point);
    }
    
    virtual Color getIntensity(const Vector3& point) const override {
        float distance = (position - point).length();
        // Sem atenuação por enquanto
        return intensity;
    }
    
    virtual float getDistance(const Vector3& point) const override {
        return (position - point).length();
    }
};

#endif // POINT_LIGHT_H 