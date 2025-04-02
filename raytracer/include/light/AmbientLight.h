#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "Light.h"

class AmbientLight {
public:
    Color intensity;  // Intensidade/cor da luz ambiente
    
    // Construtores
    AmbientLight() : intensity(0.1f, 0.1f, 0.1f) {}
    
    AmbientLight(float r, float g, float b) : intensity(r, g, b) {}
    
    AmbientLight(const Color& intensity) : intensity(intensity) {}
    
    // A luz ambiente não tem direção específica nem distância
    // É aplicada uniformemente em toda a cena
};

#endif // AMBIENT_LIGHT_H 