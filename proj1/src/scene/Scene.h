#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <limits>
#include "../core/Ray.h"
#include "../core/Color.h"
#include "../geometry/Object.h"
#include "../lighting/Light.h"
#include "Material.h"

class Scene {
public:
    Scene() {}
    
    // Adiciona um objeto à cena
    void add_object(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }
    
    // Adiciona uma luz à cena
    void add_light(std::shared_ptr<Light> light) {
        lights.push_back(light);
    }
    
    // Testa interseção do raio com todos os objetos da cena
    bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;
        
        for (const auto& object : objects) {
            if (object->hit(ray, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        
        return hit_anything;
    }
    
    // Verifica se há algum objeto bloqueando o caminho entre dois pontos (para sombras)
    bool is_shadowed(const Point3& point, const Point3& light_pos) const {
        Vector3 direction = light_pos - point;
        double distance = direction.length();
        Ray shadow_ray(point + 0.001 * normalize(direction), normalize(direction));
        
        HitRecord temp_rec;
        return hit(shadow_ray, 0.001, distance - 0.001, temp_rec);
    }
    
    // Traça um raio na cena e retorna a cor
    Color trace_ray(const Ray& ray, int depth) const {
        if (depth <= 0) {
            return Color(0, 0, 0);
        }
        
        HitRecord rec;
        if (!hit(ray, 0.001, std::numeric_limits<double>::infinity(), rec)) {
            return Color(0.05, 0.05, 0.05); // Cor de fundo
        }
        
        // Verificar se o material é válido
        if (!rec.material) {
            return Color(1, 0, 1); // Cor magenta para indicar material faltando
        }
        
        // Calcular iluminação direta
        Color color(0, 0, 0);
        
        try {
            for (const auto& light : lights) {
                if (!light) continue; // Pular luzes nulas
                
                auto samples = light->sample_multiple(rec.point, 1);
                
                for (const auto& sample : samples) {
                    if (!is_shadowed(rec.point, sample.position)) {
                        Vector3 light_dir = normalize(sample.position - rec.point);
                        Vector3 view_dir = normalize(-ray.direction());
                        
                        Color phong = rec.material->shade(rec, view_dir, light_dir, sample.intensity);
                        color += phong;
                    }
                }
            }
            
            // Reflexão - com verificação extra de segurança
            if (rec.material->is_reflective() && depth > 1) {
                Ray reflected = rec.material->reflect(ray, rec);
                color += Color(0.5, 0.5, 0.5) * trace_ray(reflected, depth - 1);
            }
        } catch (...) {
            // Em caso de exceção, retornar uma cor de erro
            return Color(1, 0, 0);
        }
        
        return color;
    }
    
    const std::vector<std::shared_ptr<Object>>& get_objects() const {
        return objects;
    }
    
    const std::vector<std::shared_ptr<Light>>& get_lights() const {
        return lights;
    }
    
private:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Light>> lights;
};

#endif 