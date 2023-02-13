#ifndef HITABLELISTH
#define HITABLELISTH

#include <hitable.h>


class HitableList: public Hitable {
    public:
        Hitable **list;
        int list_size;

        HitableList() {};
        HitableList(Hitable **l, int n) {
            list = l;
            list_size = n;
        }

        virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
};


bool HitableList::hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const {
    HitRecord temp;
    bool hit_anything = false;
    double closest_so_far = tmax;
    
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, tmin, closest_so_far, temp)) {
            hit_anything = true;
            closest_so_far = temp.t;
            rec = temp;
        }
    }

    return hit_anything;
}

#endif
