#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include "../core/Vector3.h"
#include "../core/Color.h"

struct LightSample {
    Point3 position;      // Posição da luz
    Color intensity;      // Intensidade/cor da luz
};

class Light {
public:
    virtual ~Light() = default;
    
    Light(const Color& color, double intensity = 1.0) 
        : color(color), intensity(intensity) {}
    
    // Obtém uma amostra da luz a partir de um ponto
    virtual LightSample sample(const Point3& point) const = 0;
    
    // Obtém múltiplas amostras da luz para um ponto (para luzes estendidas)
    virtual std::vector<LightSample> sample_multiple(const Point3& point, int num_samples) const {
        std::vector<LightSample> samples;
        samples.push_back(sample(point));
        return samples;
    }
    
protected:
    Color color;
    double intensity;
};

#endif 