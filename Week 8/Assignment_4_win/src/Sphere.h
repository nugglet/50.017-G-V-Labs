#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include "vecmath.h"
#include <cmath>

#include <iostream>
using namespace std;

class Sphere: public Object3D
{
public:
	Sphere()
    { 
		//unit ball at the center
        this->center = vec3(0,0,0);
        this->radius = 1.0;
	}

	Sphere( vec3 center , float radius , Material* material ):Object3D(material)
    {
        this->center = center;
        this->radius = radius;
	}
	

	~Sphere(){}

    /// TODO: implement this function for ray-sphere intersection test.
	virtual bool intersect( const Ray& r , Hit& h   , float tmin)
    {
        vec3 Rd = r.getDirection();
        vec3 Ro = r.getOrigin() - center; 

        float a = glm::dot(Rd, Rd); 
        float b = 2.0f * glm::dot(Rd, Ro);
        float c = glm::dot(Ro, Ro) - radius * radius;

        float discriminant = b * b - 4 * a * c;
        float t0 = (-b - sqrt(discriminant)) / (2.0f * a);
        float t1 = (-b + sqrt(discriminant)) / (2.0f * a);

        if (discriminant >= 0) {
            // Check t0 which should be closer to the ray origin
            if (t0 >= tmin && t0 < h.getT()) {
                vec3 normal = normalize(r.pointAtParameter(t0) - center);

                // Update Hit
                h.set(t0, material, normal);
                return true;
            }

            // Check t1
            if (t1 >= tmin && t1 < h.getT()) {
                vec3 normal = normalize(r.pointAtParameter(t1) - center);

                h.set(t1, material, normal);
                return true;
            }
        }

        return false;
	}

protected:
    vec3 center;
    float radius;
  

};


#endif
