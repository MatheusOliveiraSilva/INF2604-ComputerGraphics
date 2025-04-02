#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "../geometry/Primitive.h"
#include "../light/Light.h"
#include "../utils/Color.h"

class Scene {
private:
    std::vector<std::shared_ptr<Primitive>> objects;
    std::vector<std::shared_ptr<Light>> lights;
    Color ambientLight;

public:
    Scene() : ambientLight(0.1, 0.1, 0.1) {}
    
    // Define a luz ambiente da cena
    void setAmbientLight(const Color& ambient) {
        ambientLight = ambient;
    }
    
    // Retorna a luz ambiente da cena
    const Color& getAmbientLight() const {
        return ambientLight;
    }
    
    // Adiciona um objeto à cena
    void addObject(std::shared_ptr<Primitive> object) {
        objects.push_back(object);
    }
    
    // Adiciona uma luz à cena
    void addLight(std::shared_ptr<Light> light) {
        lights.push_back(light);
    }
    
    // Verifica intersecção com qualquer objeto da cena
    bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const {
        HitRecord tempRecord;
        bool hitAnything = false;
        double closestSoFar = tMax;
        
        for (const auto& object : objects) {
            if (object->hit(ray, tMin, closestSoFar, tempRecord)) {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                record = tempRecord;
            }
        }
        
        return hitAnything;
    }
    
    // Getters
    const std::vector<std::shared_ptr<Primitive>>& getObjects() const {
        return objects;
    }
    
    const std::vector<std::shared_ptr<Light>>& getLights() const {
        return lights;
    }
};

#endif // SCENE_H 