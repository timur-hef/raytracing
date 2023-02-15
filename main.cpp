#include <fstream>
#include <hitable_list.h>
#include <limits>
#include <random>
#include <camera.h>
#include <sphere.h>

using namespace std;


class Randomizer {
    private:
        random_device rd;
        mt19937 gen;
        uniform_real_distribution<float> dis;

    public:
        Randomizer() {
            mt19937 gen = mt19937(rd());
            uniform_real_distribution<float> dis = uniform_real_distribution((float) 0.0, (float) 0.99999);
        }

        float get_random_number() {
            return dis(gen);
        }
};


Vec random_in_unit_sphere(Randomizer &rand) {
    Vec s;

    do {
        s = 2.0 * Vec(rand.get_random_number(), rand.get_random_number(), rand.get_random_number()) - Vec(1, 1, 1);
    } while (s.squared_length() >= 1.0);

    return s;
}


Vec color(const Ray &r, Hitable *world, Randomizer &rand) {  // return color
    HitRecord rec;
    if (world->hit(r, 0.001, numeric_limits<float>::max(), rec)) {  // if hits one of hitable objects in world
        Vec target = rec.p + rec.normal + random_in_unit_sphere(rand);
        return 0.7 * color(Ray(rec.p, target - rec.p), world, rand);  // coef means reduce of intencity of the reflected light
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

    Hitable *list[2];
    list[0] = new Sphere(Vec(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec(0, -100.5, -1), 100);
    Hitable *world = new HitableList(list, 2);
    Camera camera;
    Randomizer rand;

    for (int j = ny - 1; j >= 0; j--) {
        cout << "j: " << j << endl;
        for (int i = 0; i < nx; i++) {
            Vec c(0, 0, 0);

            for (int s = 0; s < ns; s++) {
                float u = float(i + rand.get_random_number()) / float(nx);
                float v = float(j + rand.get_random_number()) / float (ny);   
                Ray r = camera.get_ray(u, v);
                c = c + color(r, world, rand);
            }

            c = c / float(ns);
            int ir = int(255.0 * sqrt(c.r()));
            int ig = int(255.0 * sqrt(c.g()));
            int ib = int(255.0 * sqrt(c.b()));
            out << ir << " " << ig << " " << ib << "\n"; 
        }
    }

    out.close();
    delete list[0];
    delete list[1];
    delete world;
}