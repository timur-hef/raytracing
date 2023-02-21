#include <fstream>
#include <hitable_list.h>
#include <limits>
#include <camera.h>
#include <material.h>
#include <randomizer.h>
#include <sphere.h>
#include <typeinfo>

using namespace std;


Vec color(const Ray &r, Hitable *world, int depth) {  // return color
    HitRecord rec;
    if (world->hit(r, 0.001, numeric_limits<float>::max(), rec)) {  // if hits one of hitable objects in world
        Ray scattered;
        Vec attenuation;
        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        return Vec(0, 0, 0);
    }

    Vec unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);  // interpolation between white and blue
}


int main() {
    ofstream out;
    out.open("test.ppm"); 

    int nx = 200;
    int ny = 100;
    int ns = 100;

    out << "P3\n" << nx << " " << ny << "\n255\n";

    Vec lower_left_corner(-2.0, -1.0, -1.0);
    Vec horizontal(4.0, 0.0, 0.0);
    Vec vertical(0.0, 2.0, 0.0);
    Vec origin(0.0, 0.0, 0.0);

    Hitable *list[4];
    list[0] = new Sphere(Vec(0, 0, -1), 0.5, new Lambertian(Vec(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vec(0, -100.5, -1), 100, new Lambertian(Vec(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vec(1, 0, -1), 0.5, new Metal(Vec(0.8, 0.6, 0.2)));
    list[3] = new Sphere(Vec(-1, 0, -1), 0.5, new Metal(Vec(0.8, 0.8, 0.8)));
    Hitable *world = new HitableList(list, 4);
    Camera camera;
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec c(0, 0, 0);

            for (int s = 0; s < ns; s++) {
                float u = float(i + Randomizer::get_random_number()) / float(nx);
                float v = float(j + Randomizer::get_random_number()) / float (ny); 
                Ray r = camera.get_ray(u, v);
                c = c + color(r, world, 0);
            }

            c = c / float(ns);
            c = Vec(sqrt(c.r()), sqrt(c.g()), sqrt(c.b()));
            int ir = int(255.0 * sqrt(c.r()));
            int ig = int(255.0 * sqrt(c.g()));
            int ib = int(255.0 * sqrt(c.b()));
            out << ir << " " << ig << " " << ib << "\n"; 
            
        } 
    }

    out.close();
    delete list[0];
    delete list[1];
    delete list[2];
    delete list[3];
    delete world;
}