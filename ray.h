#ifndef RAYH
#define RAYH
#include <vec.h>

class Ray {
    public:
        Vec a;
        Vec b;

        Ray() {};
        Ray(const Vec &a, const Vec &b): a(a), b(b) {};

        Vec origin() const {return a;};
        Vec direction() const {return b;};
        Vec point_at_parameter(float t) const {return a + t * b;};
};

#endif