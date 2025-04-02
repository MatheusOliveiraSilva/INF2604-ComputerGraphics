#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Primitive.h"
#include "../light/Light.h"
#include "../light/AmbientLight.h"
#include "../material/Material.h"

class Scene {
public:
    std::vector<Primitive*> objects;
    std::vector<Light*> lights;
    AmbientLight ambientLight;
    
    // Construtores
    Scene() : ambientLight() {}
    
    Scene(const AmbientLight& ambientLight) : ambientLight(ambientLight) {}
    
    // Adiciona um objeto à cena
    void addObject(Primitive* object) {
        objects.push_back(object);
    }
    
    // Adiciona uma fonte de luz à cena
    void addLight(Light* light) {
        lights.push_back(light);
    }
    
    // Define a luz ambiente da cena
    void setAmbientLight(const AmbientLight& light) {
        ambientLight = light;
    }
    
    // Verifica se um raio atinge algum objeto na cena
    bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {
        HitRecord tempRecord;
        bool hitAnything = false;
        float closestSoFar = tMax;
        
        // Verificar interseção com cada objeto
        for (const auto& object : objects) {
            if (object->hit(ray, tMin, closestSoFar, tempRecord)) {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                record = tempRecord;
            }
        }
        
        return hitAnything;
    }
    
    // Verifica se há sombra entre um ponto e uma luz
    bool isShadowed(const Vector3& point, const Light* light) const {
        Vector3 lightDir = light->getDirection(point);
        float lightDist = light->getDistance(point);
        
        // Usar uma pequena distância de offset para evitar auto-sombreamento
        const float shadowEpsilon = 0.001f;
        
        // Raio da sombra (do ponto para a luz)
        Ray shadowRay(point + lightDir * shadowEpsilon, lightDir);
        
        // Verificar interseção com os objetos, ignorando objetos emissivos
        HitRecord tempRecord;
        for (const auto& object : objects) {
            // Se o objeto for a fonte de luz, ignorar
            if (object->hit(shadowRay, shadowEpsilon, lightDist - shadowEpsilon, tempRecord)) {
                // Verificar se é um objeto emissor de luz (lâmpada)
                if (tempRecord.material) {
                    const Color& ambient = tempRecord.material->ambient;
                    if (ambient.r >= 0.9f && ambient.g >= 0.9f && ambient.b >= 0.9f) {
                        continue;  // Ignorar objetos emissores de luz
                    }
                }
                return true; // Há um objeto bloqueando a luz
            }
        }
        
        return false; // Nenhum objeto bloqueando a luz
    }
};

#endif // SCENE_H 