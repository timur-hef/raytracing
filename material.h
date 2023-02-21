#ifndef MATERIALH
#define MATERIALH

#include <ray.h>
#include <hitable.h>


class Material {
    public:
        virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec &attentuation, Ray &scattered) const = 0;
};


class Lambertian : public Material {
    public:
        Vec albedo;

        Lambertian(const Vec &a): albedo(a) {};

        virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec &attentuation, Ray &scattered) const {
            Vec target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = Ray(rec.p, target - rec.p);
            attentuation = albedo;
            return true;
        }
};


class Metal : public Material {
    public:
        Vec albedo;

        Metal(const Vec &a): albedo(a) {};

        virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec &attentuation, Ray &scattered) const {
            Vec reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected);
            attentuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
};


#endif