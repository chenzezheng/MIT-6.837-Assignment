#ifndef _GROUP_H_
#define _GROUP_H_

#include <vector>
#include "object3d.h"
#include "grid.h"

class Group : public Object3D {
private:
    vector<Object3D *> objects;
public:
    Group(int size);
    ~Group();
    void addObject(int index, Object3D *obj);
    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
    void insertIntoGrid(Grid *g, Matrix *m);
};

#endif