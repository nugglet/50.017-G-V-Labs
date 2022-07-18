#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include "vecmath.h"
#include "VecUtils.h"

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"


class Material
{
public:
	
    Material( const vec3& d_color ,const vec3& s_color=vec3(0,0,0), float s=0):
    diffuseColor( d_color),specularColor(s_color), shininess(s)
    {

    }

    virtual ~Material()
      {

      }

    virtual vec3 getDiffuseColor() const 
    { 
      return  diffuseColor;
    }
      
    /// TODO: Implement this function to compute diffuse and specular components of Phong lighting 
    vec3 Shade( const Ray& ray, const Hit& hit, const vec3& dirToLight, const vec3& lightColor ) 
    {
        vec3 N = normalize(hit.getNormal());

        float diffuseShading = glm::dot(N, dirToLight);
        // Clamp diffuseShading
        if (diffuseShading < 0)
            diffuseShading = 0;

        vec3 diffuseComponent;
        if (t.valid()) {
            vec3 textureColor = t(hit.texCoord[0], hit.texCoord[1]);
            diffuseComponent = diffuseShading * lightColor * textureColor;
        }
        else {
            diffuseComponent = diffuseShading * lightColor * diffuseColor;
        }

        /*** Specular Component ***/
        vec3 R = 2 * diffuseShading * N - dirToLight;
        vec3 V = normalize(- ray.getDirection());

        float specularShading = glm::dot(V, R);
        if (specularShading < 0)
            specularShading = 0;

        vec3 specularComponent = pow(specularShading, shininess) * lightColor * specularColor;

        return diffuseComponent + specularComponent;
    }

    void loadTexture(const char * filename)
    {
      t.load(filename);
    }

    Texture t;

 protected:
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
};



#endif // MATERIAL_H
