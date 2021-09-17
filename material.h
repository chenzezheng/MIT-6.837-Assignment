#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "hit.h"
#include "ray.h"
#include "vectors.h"

// ====================================================================
// ====================================================================

// You will extend this class in later assignments

class Material
{

public:
  // CONSTRUCTORS & DESTRUCTOR
  Material(const Vec3f &d_color) { diffuseColor = d_color; }
  virtual ~Material() {}

  // ACCESSORS
  virtual Vec3f getDiffuseColor() const { return diffuseColor; }
  virtual Vec3f getSpecularColor() const = 0;
  virtual Vec3f getReflectiveColor() const = 0;
  virtual Vec3f getTransparentColor() const = 0;
  virtual float getIndexOfRefraction() const = 0;
  virtual void glSetMaterial(void) const = 0;
  virtual Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight,
                      const Vec3f &lightColor) const = 0;

protected:
  // REPRESENTATION
  Vec3f diffuseColor;
};

// ====================================================================
// ====================================================================

class PhongMaterial : public Material {
public:
    PhongMaterial(const Vec3f &d_color) :
            Material(d_color), specularColor(Vec3f(0, 0, 0)), exponent(0) {}
    PhongMaterial(const Vec3f &d_color, const Vec3f &s_color, float e, const Vec3f &ref_color, const Vec3f &trans_color, float index) :
            Material(d_color), specularColor(s_color), exponent(e), reflectiveColor(ref_color), transparentColor(trans_color), indexOfRefraction(index) {}
    ~PhongMaterial() {}

    virtual Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight,
                        const Vec3f &lightColor) const;
    virtual void glSetMaterial() const;
    Vec3f getSpecularColor() const { return specularColor; }
    Vec3f getReflectiveColor() const { return reflectiveColor; }
    Vec3f getTransparentColor() const { return transparentColor; }
    float getIndexOfRefraction() const { return indexOfRefraction; }

private:
    Vec3f specularColor;
    float exponent;
    Vec3f reflectiveColor;
    Vec3f transparentColor;
    float indexOfRefraction;
};

#endif
