#include <cmath>
#include <vector>
#include "sphere.h"

extern int theta_steps;
extern int phi_steps;
extern bool isGouraud;
const float PI = 3.141592653589793;

float square(float x) {
    return x * x;
}

Sphere::Sphere(Vec3f &c, float r, Material *m) {
    center = c;
    radius = r;
    material = m;
    boundingBox = new BoundingBox(center - Vec3f(r, r, r), center + Vec3f(r, r, r));
}

bool Sphere::intersect(const Ray &r, Hit &h, float tmin) {
    Vec3f ro = r.getOrigin() - center;
    Vec3f rd = r.getDirection();

    float a = rd.Dot3(rd);
    float b = 2 * ro.Dot3(rd);
    float c = ro.Dot3(ro) - radius * radius;
    float delta = b * b - 4 * a * c;
    float t = INFINITY;
    if (delta >= 0) {
        float d = sqrt(delta);
        float t1 = (-b - d) / (2 * a);
        float t2 = (-b + d) / (2 * a);
        if (t1 >= tmin) {
            t = t1;
        } else if (t2 >= tmin) {
            t = t2;
        }
        if (t < h.getT()) {
            Vec3f normal = ro + t * rd;
            normal.Normalize();
            h.set(t, material, normal, r);
            return true;
        }
    }
    return false;
}

// bool Sphere::intersect(const Ray &r, Hit &h, float tmin) {
//     Vec3f OC = center - r.getOrigin();
//     Vec3f Rd = r.getDirection();
//     float dirLength = r.getDirection().Length();
//     Rd.Normalize();
//     float tp = OC.Dot3(Rd);
//     float d2 = OC.Dot3(OC) - square(tp);
//     if (d2 > square(radius)) return false;
//     float t = sqrt(square(radius) - d2);
//     if ((tp - t) / dirLength > tmin) {
//         Vec3f intersectPoint = r.pointAtParameter((tp - t) / dirLength);
//         Vec3f normal = intersectPoint - center;
//         normal.Normalize();
//         if ((tp - t) / dirLength < h.getT()) {
//             h.set((tp - t) / dirLength, material, normal, r);
//             return true;
//         }
//     } else if ((tp + t) / dirLength > tmin) {
//         Vec3f intersectPoint = r.pointAtParameter((tp + t) / dirLength);
//         Vec3f normal = intersectPoint - center;
//         normal.Normalize();
//         if ((tp + t) / dirLength < h.getT()) {
//             h.set((tp + t) / dirLength, material, normal, r);
//             return true;
//         }
//     }
//     return false;
// }

void Sphere::paint() {
    float deltaTheta = 2 * PI / theta_steps;
    float deltaPhi = PI / phi_steps;
    vector<Vec3f> vertex;
    vector<Vec3f> normal;
    for(int iPhi = 0; iPhi <= phi_steps; iPhi ++ ) {
        for (int iTheta = 0; iTheta < theta_steps; iTheta ++ ) {
            float theta = iTheta * deltaTheta;
            float phi = iPhi * deltaPhi;
            Vec3f v = Vec3f(sin(phi) * cos(theta), cos(phi), sin(phi) * sin(theta));
            normal.push_back(v);
            vertex.push_back(center + radius * v);
        }
    }

    material->glSetMaterial();
    glBegin(GL_QUADS);
    for(int iPhi = 0; iPhi < phi_steps; iPhi ++ ) {
        for (int iTheta = 0; iTheta < theta_steps; iTheta ++ ) {
            int a = iPhi * theta_steps + iTheta;
            int b = (iPhi + 1) * theta_steps + iTheta;
            int c = (iPhi + 1) * theta_steps + (iTheta + 1) % theta_steps;
            int d = iPhi * theta_steps + (iTheta + 1) % theta_steps;
            if (isGouraud) {
                glNormal3f(normal[a].x(), normal[a].y(), normal[a].z());
                glVertex3f(vertex[a].x(), vertex[a].y(), vertex[a].z());
                glNormal3f(normal[b].x(), normal[b].y(), normal[b].z());
                glVertex3f(vertex[b].x(), vertex[b].y(), vertex[b].z());
                glNormal3f(normal[c].x(), normal[c].y(), normal[c].z());
                glVertex3f(vertex[c].x(), vertex[c].y(), vertex[c].z());
                glNormal3f(normal[d].x(), normal[d].y(), normal[d].z());
                glVertex3f(vertex[d].x(), vertex[d].y(), vertex[d].z());
            } else {
                Vec3f n;
                Vec3f::Cross3(n, vertex[a] - vertex[b], vertex[c] - vertex[b]);
                glNormal3f(n.x(), n.y(), n.z());
                glVertex3f(vertex[a].x(), vertex[a].y(), vertex[a].z());
                glVertex3f(vertex[b].x(), vertex[b].y(), vertex[b].z());
                glVertex3f(vertex[c].x(), vertex[c].y(), vertex[c].z());
                glVertex3f(vertex[d].x(), vertex[d].y(), vertex[d].z());
            }
        }
    }
    glEnd();
}

void Sphere::insertIntoGrid(Grid *g, Matrix *m) {
    Vec3f gridMin = (g->getBoundingBox())->getMin();
    Vec3f gridMax = (g->getBoundingBox())->getMax();
    Vec3f gridLength = gridMax - gridMin;
    Vec3f cells = g->getNumCells();
    int nx = int(cells.x() + 1e-5);
    int ny = int(cells.y() + 1e-5);
    int nz = int(cells.z() + 1e-5);
    float xlen = gridLength.x() / cells.x();
    float ylen = gridLength.y() / cells.y();
    float zlen = gridLength.z() / cells.z();

    if (m) {
        Vec3f bound[2] = {boundingBox->getMin(), boundingBox->getMax()};
        BoundingBox *transformedBoundingBox = NULL;
        for (int i = 0; i < 8; i ++ ) {
            int x = i & 1, y = (i >> 1) & 1, z = (i >> 2) & 1;
            Vec3f v = Vec3f(bound[x].x(), bound[y].y(), bound[z].z());
            m->Transform(v);
            if (!transformedBoundingBox) {
                transformedBoundingBox = new BoundingBox(v, v);
            } else {
                transformedBoundingBox->Extend(v);
            }
        }

        Vec3f sphMin = transformedBoundingBox->getMin();
        Vec3f sphMax = transformedBoundingBox->getMax();
        int sti = int((sphMin - gridMin).x() / xlen);
        int stj = int((sphMin - gridMin).y() / ylen);
        int stk = int((sphMin - gridMin).z() / zlen);
        int eni = int((sphMax - gridMin).x() / xlen);
        int enj = int((sphMax - gridMin).y() / ylen);
        int enk = int((sphMax - gridMin).z() / zlen);
        if (sti > nx || stj > ny || stk > nz ||
            eni < 0 || enj < 0 || enk < 0) return;
        sti = max(sti, 0);
        stj = max(stj, 0);
        stk = max(stk, 0);
        eni = min(eni, nx - 1);
        enj = min(enj, ny - 1);
        enk = min(enk, nz - 1);
        if (sti == nx) sti --;
        if (stj == ny) stj --;
        if (stk == nz) stk --;

        for (int i = sti; i <= eni; i ++ ) {
            for (int j = stj; j <= enj; j ++ ) {
                for (int k = stk; k <= enk; k ++ ) {
                    g->addObject(Vec3f(i, j, k), this);
                }
            }
        }
        return;
    }

    float diagonal = sqrt(square(xlen) + square(ylen) + square(zlen));
    for (int i = 0; i < nx; i ++ ) {
        for (int j = 0; j < ny; j ++ ) {
            for (int k = 0; k < nz; k ++ ) {
                Vec3f v = Vec3f((i + 0.5) * xlen,
                                (j + 0.5) * ylen,
                                (k + 0.5) * zlen) + gridMin;
                if ((v - center).Length() < radius + diagonal / 2.0) {
                    g->addObject(Vec3f(i, j, k), this);
                }
            }
        }
    }
}