#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "object3d.h"
#include "vectors.h"
#include "grid.h"

class Sphere : public Object3D {
private:
    Vec3f center;
    float radius;
public:
    Sphere(Vec3f &c, float r, Material *m);
    ~Sphere();
    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
    void insertIntoGrid(Grid *g, Matrix *m);
};

#endif