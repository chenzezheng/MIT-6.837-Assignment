#ifndef _PLANE_H_
#define _PLANE_H_

#include "object3d.h"
#include "vectors.h"
#include "grid.h"

class Plane : public Object3D {
private:
    Vec3f normal;
    float dist;
public:
    Plane(Vec3f &n, float d, Material *m);
    ~Plane();
    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
    void insertIntoGrid(Grid *g, Matrix *m);
};

#endif