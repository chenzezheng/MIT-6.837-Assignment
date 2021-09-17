#include "object3d.h"

Object3D::Object3D() {

}

Object3D::~Object3D() {
    
}

bool Object3D::isTriangle() {
    return false;
}

BoundingBox* Object3D::getBoundingBox() {
    return boundingBox;
}

void Object3D::insertIntoGrid(Grid *g, Matrix *m) {

}

BoundingBox* Object3D::getTransformedBoundingBox(const Matrix *matrix) const {
    return NULL;
}