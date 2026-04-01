#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <strstream>
#include "mathem.hpp"

struct triangle
{
    std::vector<Vecd> p;
    Vecd normal;
    triangle() { p = std::vector<Vecd>(3); }
    triangle(std::vector<Vecd> P) { p = P; }
    triangle(Vecd p1, Vecd p2, Vecd p3) { p = std::vector<Vecd>(3); p[0] = p1; p[1] = p2; p[2] = p3; };
    std::vector<triangle> clip_fun(Vecd plane_p, Vecd plane_n)
    {
        plane_n.norm();

        auto dist = [&](Vecd& p)
            {
                Vecd n = p;
                n.norm();
                return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - dot_prod(plane_n, plane_p));
            };

        Vecd inside[3];  int inside_count = 0;
        Vecd outside[3]; int outside_count = 0;

        for (int i = 0; i < 3; i++)
        {
            if (dist(this->p[i]) >= 0)
            {
                inside[inside_count++] = this->p[i];
            }
            else
            {
                outside[outside_count++] = this->p[i];
            }
        }

        if (inside_count == 0) return std::vector<triangle>(0);
        if (inside_count == 3) return std::vector<triangle>(1, *this);
        if (inside_count == 1 && outside_count == 2)
        {
            float t;
            triangle out;
            out.p[0] = inside[0];

            out.p[1] = intersectPlane(plane_p, plane_n, inside[0], outside[0], t);

            out.p[2] = intersectPlane(plane_p, plane_n, inside[0], outside[1], t);

            out.normal = normal;

            return std::vector<triangle>{ out };
        }
        if (inside_count == 2 && outside_count == 1)
        {
            triangle out1, out2;
            float t;

            out1.p[0] = inside[0];
            out1.p[1] = inside[1];
            out1.p[2] = intersectPlane(plane_p, plane_n, inside[0], outside[0], t);
            out1.normal = normal;

            out2.p[0] = inside[1];
            out2.p[1] = out1.p[2];
            out2.p[2] = intersectPlane(plane_p, plane_n, inside[1], outside[0], t);
            out2.normal = normal;

            return std::vector<triangle>{ out1, out2 };
        }
    }
};

class mesh
{
public:
    std::vector<triangle> tris;
    mesh() { tris = {}; }
    mesh(std::vector<triangle>& TRIS) : tris(TRIS) {}
    bool load_from_file(char* file_name)
    {
        this->tris = std::vector<triangle>();
        std::ifstream file(file_name);
        if (!file.is_open()) return 0;
        std::vector<Vecd> verts;

        while (!file.eof())
        {
            char line[128];
            file.getline(line, 128);
            std::strstream s;
            s << line;

            char j = 0;
            if (line[0] == 'v')
            {
                Vecd v;
                s >> j >> v.x >> v.y >> v.z;
                verts.push_back(v);
            }
            if (line[0] == 'f')
            {
                std::vector<int> f(3);
                bool flag = 0;
                for (auto p : line)
                {
                    if (p == '/')
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                {
                    int foo;
                    s >> j >> f[0] >> j >> foo >> f[1] >> j >> foo >> f[2] >> j >> foo;
                }
                else
                {
                    s >> j >> f[0] >> f[1] >> f[2];
                }
                triangle t(verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1]);
                this->tris.push_back(t);
            }
        }
        return true;
    }
    void define_as_cube()
    {
        this->tris = {

            // SOUTH
            triangle{ Vecd(0.0f, 0.0f, 0.0f),    Vecd(0.0f, 1.0f, 0.0f),    Vecd(1.0f, 1.0f, 0.0f) },
            triangle{ Vecd(0.0f, 0.0f, 0.0f),    Vecd(1.0f, 1.0f, 0.0f),    Vecd(1.0f, 0.0f, 0.0f) },
            // EAST                                                                         
            triangle(Vecd(1.0f, 0.0f, 0.0f),    Vecd(1.0f, 1.0f, 0.0f),    Vecd(1.0f, 1.0f, 1.0f)),
            triangle(Vecd(1.0f, 0.0f, 0.0f),    Vecd(1.0f, 1.0f, 1.0f),    Vecd(1.0f, 0.0f, 1.0f)),
            // NORTH                                                                        
            triangle(Vecd(1.0f, 0.0f, 1.0f),    Vecd(1.0f, 1.0f, 1.0f),    Vecd(0.0f, 1.0f, 1.0f)),
            triangle(Vecd(1.0f, 0.0f, 1.0f),    Vecd(0.0f, 1.0f, 1.0f),    Vecd(0.0f, 0.0f, 1.0f)),
            // WEST                                                                         
            triangle(Vecd(0.0f, 0.0f, 1.0f),    Vecd(0.0f, 1.0f, 1.0f),    Vecd(0.0f, 1.0f, 0.0f)),
            triangle(Vecd(0.0f, 0.0f, 1.0f),    Vecd(0.0f, 1.0f, 0.0f),    Vecd(0.0f, 0.0f, 0.0f)),
            // TOP                                                                        
            triangle(Vecd(0.0f, 1.0f, 0.0f),    Vecd(0.0f, 1.0f, 1.0f),    Vecd(1.0f, 1.0f, 1.0f)),
            triangle(Vecd(0.0f, 1.0f, 0.0f),    Vecd(1.0f, 1.0f, 1.0f),    Vecd(1.0f, 1.0f, 0.0f)),
            // BOTTOM                                                                     
            triangle(Vecd(1.0f, 0.0f, 1.0f),    Vecd(0.0f, 0.0f, 1.0f),    Vecd(0.0f, 0.0f, 0.0f)),
            triangle(Vecd(1.0f, 0.0f, 1.0f),    Vecd(0.0f, 0.0f, 0.0f),    Vecd(1.0f, 0.0f, 0.0f)),
        };
    }
};