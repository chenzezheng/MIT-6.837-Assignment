#include "transform.h"

Transform::Transform(Matrix &m, Object3D *o) {
    matrix = m;
    object = o;
    if (object->isTriangle()) {
        boundingBox = object->getTransformedBoundingBox(&m);
    }
    boundingBox = object->getBoundingBox();
    Vec3f bound[2] = {boundingBox->getMin(), boundingBox->getMax()};
    boundingBox = NULL;
    for (int i = 0; i < 8; i ++ ) {
        int x = i & 1, y = (i >> 1) & 1, z = (i >> 2) & 1;
        Vec3f v = Vec3f(bound[x].x(), bound[y].y(), bound[z].z());
        matrix.Transform(v);
        if (!boundingBox) {
            boundingBox = new BoundingBox(v, v);
        } else {
            boundingBox->Extend(v);
        }
    }
}

bool Transform::intersect(const Ray & r, Hit & h, float tmin)
{
	Vec4f origin = Vec4f(r.getOrigin(), 1.0);
	Vec4f direction = Vec4f(r.getDirection(), 0.0);
	Matrix invMatrix = matrix;
	if (invMatrix.Inverse()) {
        invMatrix.Transform(origin);
        invMatrix.Transform(direction);
        Ray invRay = Ray(Vec3f(origin.x(), origin.y(), origin.z()),Vec3f(direction.x(), direction.y(), direction.z()));
        if (object->intersect(invRay, h, tmin))
        {
            Vec4f invNormal = Vec4f(h.getNormal(), 0.0);
            invMatrix.Transpose();
            invMatrix.Transform(invNormal);
            Vec3f normal = Vec3f(invNormal.x(), invNormal.y(), invNormal.z());
            normal.Normalize();
            h.set(h.getT(), h.getMaterial(), normal, r);
            return true;
        }
    }
	return false;
}

void Transform::paint() {
    glPushMatrix();
    GLfloat *glMatrix = matrix.glGet();
    glMultMatrixf(glMatrix);
    delete[] glMatrix;
    object->paint();
    glPopMatrix();
}

void Transform::insertIntoGrid(Grid *g, Matrix *m) {
    if (m) {
        Matrix temp = (*m) * matrix;
        object->insertIntoGrid(g, &temp);
    } else {
        object->insertIntoGrid(g, &matrix);
    }
}