#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>
using namespace std;


class Plane: public Object3D
{
public:
	Plane(){}

	Plane( const vec3& normal , float d , Material* m):Object3D(m)
    {
        this->normal = normalize(normal);
        this->d = -d;
        this->material = m;
	}

	~Plane(){}

    /// TODO: implement this function for ray-plane intersection test.
	virtual bool intersect( const Ray& r , Hit& h , float tmin)
    {   
        vec3 r_o = r.getOrigin();
        vec3 r_d = r.getDirection();

        float t_value = -1.0f * (-1.0f * d + glm::dot(this->normal, r_o)) / (glm::dot(this->normal, r_d));

        if (t_value > tmin && t_value < h.getT()) {
            h.set(t_value, material, this->normal);
            return true;
        }


        return false;
	}

protected:
    vec3 normal;
    float d;

    
};
#endif //PLANE_H
		

