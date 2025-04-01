#ifndef MATERIAL_H
#define MATERIAL_H

#include <algorithm>
#include <cmath>
#include "../core/Vector3.h"
#include "../core/Ray.h"
#include "../core/Color.h"
#include "../geometry/Object.h"

class Material {
public:
    virtual ~Material() = default;

    // Propriedades do material (modelo Phong)
    Color ambient;    // Ka - componente ambiente
    Color diffuse;    // Kd - componente difuso
    Color specular;   // Ks - componente especular
    double shininess; // α - expoente de Phong
    
    Material(const Color& ambient, const Color& diffuse, const Color& specular, double shininess)
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}
    
    // Calcula a cor baseada no modelo Phong para uma interseção
    virtual Color shade(const HitRecord& rec, const Vector3& view_dir, const Vector3& light_dir, const Color& light_color) const {
        // Componente ambiente
        Color result = ambient * light_color;
        
        // Sanitizar entradas para evitar NaN e infinito
        Vector3 safe_normal = rec.normal;
        if (safe_normal.near_zero()) {
            safe_normal = Vector3(0, 1, 0); // Normal padrão se a normal for inválida
        }
        
        Vector3 safe_light_dir = light_dir;
        if (safe_light_dir.near_zero()) {
            return result; // Retorna apenas o componente ambiente se a luz for inválida
        }
        
        Vector3 safe_view_dir = view_dir;
        if (safe_view_dir.near_zero()) {
            safe_view_dir = -safe_light_dir; // Direção de visualização padrão se for inválida
        }
        
        // Componente difuso (lei do cosseno de Lambert)
        double cos_theta = std::max(dot(safe_normal, safe_light_dir), 0.0);
        result += diffuse * light_color * cos_theta;
        
        // Componente especular
        if (cos_theta > 0) {
            Vector3 reflected = reflect(-safe_light_dir, safe_normal);
            double spec = std::pow(std::max(dot(safe_view_dir, reflected), 0.0), std::max(shininess, 1.0));
            result += specular * light_color * spec;
        }
        
        return result;
    }
    
    // Determina se este material gera reflexões
    virtual bool is_reflective() const { return false; }
    
    // Determina se este material refrata luz
    virtual bool is_refractive() const { return false; }
    
    // Calcula o raio refletido (para materiais reflexivos)
    virtual Ray reflect(const Ray& ray_in, const HitRecord& rec) const {
        Vector3 reflected = reflect(normalize(ray_in.direction()), rec.normal);
        return Ray(rec.point + 0.001 * rec.normal, reflected); // Adicionar pequeno offset para evitar auto-interseção
    }
    
protected:
    // Função utilitária para calcular vetor de reflexão
    Vector3 reflect(const Vector3& v, const Vector3& n) const {
        return v - 2 * dot(v, n) * n;
    }
};

#endif 