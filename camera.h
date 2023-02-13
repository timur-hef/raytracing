#ifndef CAMERAH
#define CAMERAH

#include <ray.h>

class Camera {
    public:
        Vec origin;  // location of eye or camera
        Vec lower_left_corner;
        Vec horizontal;
        Vec vertical;

        Camera() {
            lower_left_corner = Vec(-2.0, -1.0, -1.0);
            horizontal = Vec(4.0, 0.0, 0.0);
            vertical = Vec(0.0, 2.0, 0.0);
            origin = Vec(0.0, 0.0, 0.0);
        };

        Ray get_ray(float u, float v) {
            return Ray(origin , lower_left_corner + u * horizontal + v * vertical - origin);
        }
};

#endif