#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera {
public:
    Point3 origin;         // Posição da câmera
    Point3 lower_left_corner;  // Canto inferior esquerdo do viewport
    Vec3 horizontal;       // Vetor horizontal do viewport
    Vec3 vertical;         // Vetor vertical do viewport

    Camera(
        Point3 lookfrom = Point3(0, 0, 0),
        Point3 lookat = Point3(0, 0, -1),
        Vec3 vup = Vec3(0, 1, 0),
        double vfov = 90.0,  // Campo de visão vertical em graus
        double aspect_ratio = 16.0 / 9.0
    ) {
        double theta = vfov * M_PI / 180.0;
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;

        // Construção da base ortonormal (u, v, w)
        Vec3 w = (lookfrom - lookat).normalized();
        Vec3 u = cross(vup, w).normalized();
        Vec3 v = cross(w, u);

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    }

    // Gera um raio partindo da câmera e passando pelo ponto (s, t) do viewport
    Ray get_ray(double s, double t) const {
        return Ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
    }
};

#endif // CAMERA_H 