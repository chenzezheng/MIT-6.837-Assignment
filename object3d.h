#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <GL/freeglut.h>
#include "ray.h"
#include "hit.h"
#include "material.h"
#include "boundingbox.h"
#include "matrix.h"

class Grid;

class Object3D {
public:
    Object3D();
    ~Object3D();
    virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
    virtual void paint() = 0;
    virtual bool isTriangle();
    virtual BoundingBox* getBoundingBox();
    virtual BoundingBox* getTransformedBoundingBox(const Matrix *matrix) const;
    virtual void insertIntoGrid(Grid *g, Matrix *m);
protected:
    Material *material;
    BoundingBox *boundingBox;
};

#endif