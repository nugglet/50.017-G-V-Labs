#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vecmath.h"
#include "VecUtils.h"
#include "Object3D.h"

class Transform: public Object3D
{
public: 
    Transform(){}

    Transform( const mat4& m, Object3D* obj) :o(obj)
    {
      this->m = m;
      this->o = obj;
    }

    ~Transform()
    {

    }
    /// TODO: implement this function so that the intersect function first transforms the ray into the object's local coordindate frame
    virtual bool intersect( const Ray& r , Hit& h , float tmin)
    {
        mat4 inv_m = glm::inverse(m);
        
        vec3 origin_ws = r.getOrigin();
        vec3 origin_os = VecUtils::transformPoint(inv_m, origin_ws);

        vec3 direction_ws = r.getDirection();
        vec3 direction_os = VecUtils::transformDirection(inv_m, direction_ws);
        
        Ray transformedRay = Ray(origin_os, direction_os);

        bool update = this->o->intersect(transformedRay, h, tmin);

        if (update) {
            vec3 transformedNormal = normalize(VecUtils::transformDirection(transpose(inv_m), h.getNormal()));
            h.set(h.getT(), h.getMaterial(), transformedNormal);
        }

        return update;
    }

 protected:
    Object3D* o; //un-transformed object
    mat4 m;
};

#endif //TRANSFORM_H
