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
    friend Vecd cross_prod(Vecd a, Vecd b) { return Vecd(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
    float len() { return sqrt(x * x + y * y + z * z); }
    void norm() { *this /= sqrt(x * x + y * y + z * z); } // 
};

inline Vecd intersectPlane(Vecd& plane_p, Vecd& plane_n, Vecd& LineStart, Vecd& lineEnd, float & t){
    plane_n.norm();
    float plane_d = -dot_prod(plane_n,plane_p);
    float bd = dot_prod(lineEnd, plane_n);
    t = (-plane_d - ad) / (bd - ad);
    Vecd lineStartToEnd = lineEnd - LineStart;
    Vecd lineToIntersect = lineStartToEnd * t;
    return LineStart + lineToIntersect;
}

class matr4x4{
public:
    float m[4][4] = { 0 };
    matr4x4() {}
    matr4x4(std::vector<std::vector<float>> v){
        for(int i; i < 4; i++){
            for(int j = 0; j < 4; j++){
                m[i][j] = v[i][j];
            }
        }
    }

    static const matr4x4 get_proj_mat(const int width = 1920,
                              const int height = 1080,
                              const float fNear = 0.1,
                              const float fFar = 1000,
                              const float FOV = 90)
    {
        const float PI = 3.14159;
        return matr4x4(std::vector<std::vector<float>> {
            {((float)height / (float)width) / tanf(FOV / 2 / 180 * PI), 0, 0, 0},
            { 0, 1 / tanf(FOV / 2 / 180 * PI), 0, 0 },
            { 0, 0, fFar / (fFar - fNear), 1 },
            { 0, 0, -fFar * fNear / (fFar - fNear), 0 }
        });
    }
};