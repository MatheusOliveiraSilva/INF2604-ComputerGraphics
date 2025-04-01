#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "../core/Ray.h"
#include "../core/Vector3.h"

class Camera {
public:
    Camera(
        Point3 look_from,
        Point3 look_at,
        Vector3 up,
        double fov,  // Vertical field-of-view in degrees
        double aspect_ratio
    ) {
        auto theta = fov * M_PI / 180.0;
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = normalize(look_from - look_at);
        u = normalize(cross(up, w));
        v = cross(w, u);

        origin = look_from;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - w;
    }

    Ray get_ray(double s, double t) const {
        return Ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
    }

private:
    Point3 origin;
    Point3 lower_left_corner;
    Vector3 horizontal;
    Vector3 vertical;
    Vector3 u, v, w;
};

#endif 