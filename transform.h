#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "object3d.h"
#include "matrix.h"
#include "grid.h"

class Transform : public Object3D {
private:
    Matrix matrix;
    Object3D *object;
public:
    Transform(Matrix &m, Object3D *o);
    ~Transform();
    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
    void insertIntoGrid(Grid *g, Matrix *m);
};

#endif