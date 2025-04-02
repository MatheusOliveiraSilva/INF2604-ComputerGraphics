#ifndef LIGHT_H
#define LIGHT_H

#include "../core/Vector3.h"
#include "../core/Color.h"

class Light {
public:
    virtual ~Light() = default;
    
    // Retorna a direção da luz a partir de um ponto
    virtual Vector3 getDirection(const Vector3& point) const = 0;
    
    // Retorna a intensidade da luz em um ponto
    virtual Color getIntensity(const Vector3& point) const = 0;
    
    // Retorna a distância do ponto até a luz
    virtual float getDistance(const Vector3& point) const = 0;
};

#endif // LIGHT_H 