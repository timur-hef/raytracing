#ifndef VECH
#define VECH

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec {
    public:
        float e[3];

        Vec() {};
        Vec(float e0, float e1, float e2) {
            e[0] = e0;
            e[1] = e1;
            e[2] = e2;
        }

        inline float x() const {return e[0];}
        inline float y() const {return e[1];}
        inline float z() const {return e[2];}
        inline float r() const {return e[0];}
        inline float g() const {return e[1];}
        inline float b() const {return e[2];}

        inline const Vec& operator+() const {return *this;}
        inline Vec operator-() const { return Vec(-e[0], -e[1], -e[2]);}

        inline Vec& operator+= (const Vec &v2);
        inline Vec& operator-= (const Vec &v2);
        inline Vec& operator*= (const Vec &v2);
        inline Vec& operator/= (const Vec &v2);
        inline Vec& operator*= (const float t);
        inline Vec& operator/= (const float t);

        inline float length() const {
            return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
        }
        inline float squared_length() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }
        inline void make_unit_vector();
};

inline std::istream& operator>>(std::istream &is, Vec &v) {
    is >> v.e[0] >> v.e[1] >> v.e[2];
    return is;
}
inline std::ostream& operator<<(std::ostream &os, const Vec &v) {
    os << v.e[0] << v.e[1] << v.e[2];
    return os;
}
inline void Vec::make_unit_vector() {
    float k = 1.0 / Vec::length();
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}


inline Vec operator+(const Vec &v1, const Vec &v2) {
    return Vec(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
inline Vec operator-(const Vec &v1, const Vec &v2) {
    return Vec(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
inline Vec operator*(const Vec &v1, const Vec &v2) {
    return Vec(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
inline Vec operator/(const Vec &v1, const Vec &v2) {
    return Vec(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
inline Vec operator*(float t, const Vec &v) {
    return Vec(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}
inline Vec operator*(const Vec &v, float t) {
    return Vec(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}
inline Vec operator/(const Vec &v, float t) {
    return Vec(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}
inline float dot(const Vec &v1, const Vec &v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}
inline Vec cross(const Vec &v1, const Vec &v2) {
    return Vec(
        v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
        -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
        v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
    );
}


inline Vec& Vec::operator+=(const Vec &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];

    return *this;
}
inline Vec& Vec::operator*=(const Vec &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];

    return *this;
}
inline Vec& Vec::operator-=(const Vec &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];

    return *this;
}
inline Vec& Vec::operator/=(const Vec &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];

    return *this;
}
inline Vec& Vec::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
}
inline Vec& Vec::operator/=(const float t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;

    return *this;
}

inline Vec unit_vector(Vec v) {
    return v / v.length();
}

#endif