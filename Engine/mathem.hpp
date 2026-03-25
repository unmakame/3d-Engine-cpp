#pragma once
#include <math.h>
#include <vector>


class Vecd{
public:
    float x, y, z, w;
    Vecd() : x(0), y(0), z(0), w(0) {}
    Vecd(float xx, float yy, float zz) : x(xx), y(yy), z(zz), w(1) {}
    friend Vecd operator + (Vecd v1, Vecd v2) {return Vecd(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);}
    friend Vecd operator - (Vecd v1, Vecd v2) {return Vecd(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);}
    friend Vecd operator * (Vecd v1, float a) {return Vecd(v1.x * a, v1.y * a, v1.z  * a); }
    friend Vecd operator / (Vecd v1, float a) {return Vecd(v1.x / a, v1.y / a, v1.z  / a); }
    void operator +=(Vecd v) {x += v.x; y += v.y; z += v.z; }
    void operator -=(Vecd v) {x -= v.x; y -= v.y; z -= v.z; }
    void operator *=(Vecd v) {x *= v.x; y *= v.y; z *= v.z; }
    void operator /=(Vecd v) {x /= v.x; y /= v.y; z /= v.z; }
    friend Vecd operator - (Vecd v) {return v * -1; }
    friend float dot_prod(Vecd v1, Vecd v2){return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
    // friend Vecd cross_prod(Vecd a, Vecd b) { return Vecd(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
    // float len() { return sqrt(x * x + y * y + z * z); }
    // void norm() { *this /= sqrt(x * x + y * y + z * z); }
};

}