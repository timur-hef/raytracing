#ifndef HITABLEH
#define HITABLEH

#include <ray.h>


class Material;


struct HitRecord {
    float t;                // parameter value of the ray at the hit point
    Vec p;                  // intersection point
    Vec normal;             // surface normal at the intersection point
    Material *material;     // material of the object
};


class Hitable {
    public:
        Material *material;
        virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const = 0;
};


#endif