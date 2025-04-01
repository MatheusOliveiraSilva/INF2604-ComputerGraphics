#ifndef REFLECTIVE_MATERIAL_H
#define REFLECTIVE_MATERIAL_H

#include "Material.h"

class ReflectiveMaterial : public Material {
public:
    ReflectiveMaterial(const Color& ambient, const Color& diffuse, const Color& specular, double shininess, double reflectivity)
        : Material(ambient, diffuse, specular, shininess), reflectivity(reflectivity) {}
    
    virtual bool is_reflective() const override {
        return true;
    }
    
    // Getter para reflectivity
    double get_reflectivity() const {
        return reflectivity;
    }
    
private:
    double reflectivity;  // Quanto o material reflete (entre 0 e 1)
};

#endif 