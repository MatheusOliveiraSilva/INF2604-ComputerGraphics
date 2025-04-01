#ifndef TRANSFORMED_OBJECT_H
#define TRANSFORMED_OBJECT_H

#include <memory>
#include "Object.h"
#include "../utils/Transform.h"

class TransformedObject : public Object {
public:
    TransformedObject(std::shared_ptr<Object> object, const Transform& transform)
        : object(object), transform(transform) {}

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override {
        if (!object) return false; // Verificação de segurança
        
        try {
            // Transformar o raio para o espaço do objeto
            Ray local_ray = transform.apply_ray(ray);
            
            if (!object->hit(local_ray, t_min, t_max, rec)) {
                return false;
            }
            
            // Transformar de volta para o espaço global
            rec.point = transform.apply_point(rec.point);
            rec.normal = normalize(transform.apply_normal(rec.normal));
            
            return true;
        } catch (...) {
            // Em caso de erro, simplesmente retorna false
            return false;
        }
    }

private:
    std::shared_ptr<Object> object;
    Transform transform;
};

#endif 