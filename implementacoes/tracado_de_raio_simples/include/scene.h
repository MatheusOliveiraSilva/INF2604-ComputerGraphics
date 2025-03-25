#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "light.h"
#include <vector>
#include <memory>

class Scene {
public:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<Light> lights;
    Color background_color;

    Scene() : background_color(0, 0, 0) {}

    // Adiciona um objeto à cena
    void add_object(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    // Adiciona uma luz à cena
    void add_light(const Light& light) {
        lights.push_back(light);
    }

    // Testa interseção com todos os objetos da cena
    bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
        HitRecord temp_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;

        for (const auto& object : objects) {
            if (object->hit(ray, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

    // Verifica se um ponto está em sombra em relação a uma luz
    bool is_shadowed(const Point3& hit_point, const Light& light) const {
        Vec3 direction = light.direction_from(hit_point);
        double distance = light.distance_from(hit_point);
        
        Ray shadow_ray(hit_point + 0.001 * direction, direction);
        HitRecord rec;
        
        // Se houver um objeto entre o ponto e a luz, o ponto está em sombra
        if (hit(shadow_ray, 0.001, distance - 0.001, rec)) {
            return true;
        }
        
        return false;
    }
};

#endif // SCENE_H 