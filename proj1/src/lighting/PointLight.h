#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const Point3& position, const Color& color, double intensity = 1.0)
        : Light(color, intensity), position(position) {}

    virtual LightSample sample(const Point3& point) const override {
        LightSample ls;
        ls.position = position;
        ls.intensity = color * intensity / (position - point).length_squared();
        return ls;
    }

private:
    Point3 position;
};

#endif 