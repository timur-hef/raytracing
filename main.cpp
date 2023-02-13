#include <fstream>
#include <hitable_list.h>
#include <limits>
#include <random>
#include <camera.h>
#include <sphere.h>

using namespace std;


Vec color(const Ray &r, Hitable *world) {  // return color
    HitRecord rec;
    if (world->hit(r, 0.0, numeric_limits<float>::max(), rec)) {
        return 0.5 * Vec(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }

    Vec unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Vec(1.0, 1.0, 1.0) + t * Vec(0.5, 0.7, 1.0);  // interpolation between white and blue
}


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
        for (int i = 0; i < nx; i++) {
            Vec c(0, 0, 0);
            cout << "i: " << i << "  j: " << j << endl;

            for (int s = 0; s < ns; s++) {
                float u = float(i + rand.get_random_number()) / float(nx);
                float v = float(j + rand.get_random_number()) / float (ny);   
                Ray r = camera.get_ray(u, v);
                c = c + color(r, world);
            }

            c = c / float(ns);
            int ir = int(255.0 * c.r());
            int ig = int(255.0 * c.g());
            int ib = int(255.0 * c.b());
            out << ir << " " << ig << " " << ib << "\n"; 
        }
    }

    out.close();
    delete list[0];
    delete list[1];
    delete world;
}