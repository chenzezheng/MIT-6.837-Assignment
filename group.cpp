#include "group.h"

Group::Group(int size) {
    objects.resize(size);
    boundingBox = NULL;
}

Group::~Group() {
    delete &objects;
}

void Group::addObject(int index, Object3D *obj) {
    objects[index] = obj;
    if (obj->getBoundingBox()) {
        if (!boundingBox) {
            boundingBox = new BoundingBox((obj->getBoundingBox())->getMin(), (obj->getBoundingBox())->getMax());
        } else {
            boundingBox->Extend(obj->getBoundingBox());
        }
    }
}

bool Group::intersect(const Ray &r, Hit &h, float tmin) {
    bool flag = false;
    for (int i = 0; i < objects.size(); i ++ ) {
        if (objects[i]) {
            flag |= objects[i]->intersect(r, h, tmin);
        }
    }
    return flag;
}

void Group::paint() {
    for (int i = 0; i < objects.size(); i ++ ) {
        objects[i]->paint();
    }
}

void Group::insertIntoGrid(Grid *g, Matrix *m) {
    for (int i = 0; i < objects.size(); i ++) {
        objects[i]->insertIntoGrid(g, m);
    }
}