#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object3d.h"
#include "vectors.h"
#include "matrix.h"
#include "grid.h"

class Triangle : public Object3D {
private:
    Vec3f a, b, c;
    Vec3f normal;
public:
    Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m);
    ~Triangle();
    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
    bool isTriangle();
    BoundingBox* getTransformedBoundingBox(const Matrix *matrix) const;
    void insertIntoGrid(Grid *g, Matrix *m);
};

#endif