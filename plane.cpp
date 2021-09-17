#include "plane.h"

Plane::Plane(Vec3f &n, float d, Material *m) {
    normal = n;
    dist = d;
    material = m;
    normal.Normalize();
    boundingBox = NULL;
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin) {
    float t = (dist - normal.Dot3(r.getOrigin())) / normal.Dot3(r.getDirection());
    if (t > tmin && t < h.getT()) {
        h.set(t, material, normal, r);
        return true;
    }
    return false;
}

void Plane::paint() {
    Vec3f v = Vec3f(1, 0, 0);
    if (abs(normal.Dot3(v) - 1) <= 1e-5) {
        v = Vec3f(0, 1, 0);
    }
    Vec3f u;
    Vec3f::Cross3(u, v, normal);
    Vec3f::Cross3(v, normal, u);
    Vec3f center = dist * normal;
    int inf = 1e4;
    Vec3f edge[4] = {center + inf * u, center + inf * v, center - inf * u, center - inf * v};

    material->glSetMaterial();
    glBegin(GL_QUADS);
        glNormal3f(normal.x(), normal.y(), normal.z());
        glVertex3f(edge[0].x(), edge[0].y(), edge[0].z());
        glVertex3f(edge[1].x(), edge[1].y(), edge[1].z());
        glVertex3f(edge[2].x(), edge[2].y(), edge[2].z());
        glVertex3f(edge[3].x(), edge[3].y(), edge[3].z());
    glEnd();
}

void Plane::insertIntoGrid(Grid *g, Matrix *m) {
    
}