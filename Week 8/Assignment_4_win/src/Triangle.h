#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>
#include <iostream>

using namespace std;

class Triangle: public Object3D
{
public:
	Triangle();
    ///@param a b c are three vertex positions of the triangle
	Triangle( const vec3& a, const vec3& b, const vec3& c, Material* m):Object3D(m)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        hasTex = false;
	}

    /// TODO: implement this function for ray-triangle intersection test.
	virtual bool intersect( const Ray& ray,  Hit& hit , float tmin)
    {
        vec3 ro = ray.getOrigin();
        vec3 rd = ray.getDirection();

        mat3 A(a.x - b.x, a.x - c.x, rd.x,
            a.y - b.y, a.y - c.y, rd.y,
            a.z - b.z, a.z - c.z, rd.z);

        mat3 beta_top(a.x - ro.x, a.x - c.x, rd.x,
            a.y - ro.y, a.y - c.y, rd.y,
            a.z - ro.z, a.z - c.z, rd.z);

        float beta = determinant(beta_top) / determinant(A);

        mat3 gamma_top(a.x - b.x, a.x - ro.x, rd.x,
            a.y - b.y, a.y - ro.y, rd.y,
            a.z - b.z, a.z - ro.z, rd.z);

        float gamma = determinant(gamma_top) / determinant(A);


        mat3 t_top(a.x - b.x, a.x - c.x, a.x - ro.x,
            a.y - b.y, a.y - c.y, a.y - ro.y,
            a.z - b.z, a.z - c.z, a.z - ro.z);

        float t = determinant(t_top) / determinant(A);

        if ((beta + gamma) <= 1 && beta >= 0 && gamma >= 0) {
            if (t<hit.getT() && t>tmin) {
                float alpha = 1.0f - beta - gamma;
                vec3 normal = alpha * normals[0] + beta * normals[1] + gamma * normals[2];

                hit.set(t, material, normal);

                vec2 newTexCoord = (alpha * this->texCoords[0] + beta * this->texCoords[1] + gamma * this->texCoords[2]);
                hit.setTexCoord(newTexCoord);

                return true;
            }
        }


        return false;
    }
    
	bool hasTex;
	vec3 normals[3];
	vec2 texCoords[3];
    
protected:
    vec3 a;
    vec3 b;
    vec3 c;

};

#endif //TRIANGLE_H
