#ifndef SPHEREH
#define SPHEREH

#include <hitable.h>
#include <iostream>

class Sphere: public Hitable {
    public:
        Vec center;
        float radius;
        Material *material;

        Sphere() {};
        Sphere(Vec cen, float r, Material *m): center(cen), radius(r), material(m){};

        virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
};


bool Sphere::hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const {
    Vec oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        float value = (-b - sqrt(discriminant)) / (2.0 * a);
        if (value < tmax && value > tmin) {
            rec.t = value;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.material = material;
            return true;
        }

        value = (-b + sqrt(discriminant)) / (2.0 * a);
        if (value < tmax && value > tmin) {
            rec.t = value;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.material = material;
            return true;
        }
    }

    return false;
}

#endif
