#include "triangle.h"
#include "matrix.h"

Triangle::Triangle(Vec3f &_a, Vec3f &_b, Vec3f &_c, Material *m) : a(_a), b(_b), c(_c) {
    material = m;
    Vec3f::Cross3(normal, b - a, c - a);
    normal.Normalize();

    Vec3f minVertex = Vec3f(min(a.x(), min(b.x(), c.x())),
                            min(a.y(), min(b.y(), c.y())),
                            min(a.z(), min(b.z(), c.z())));
    Vec3f maxVertex = Vec3f(max(a.x(), max(b.x(), c.x())),
                            max(a.y(), max(b.y(), c.y())),
                            max(a.z(), max(b.z(), c.z())));
    boundingBox = new BoundingBox(minVertex, maxVertex);
}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin) {
    float beta, gamma, t;
    float A;
    A = det3x3(
        a.x() - b.x(), a.x() - c.x(), r.getDirection().x(),
        a.y() - b.y(), a.y() - c.y(), r.getDirection().y(),
        a.z() - b.z(), a.z() - c.z(), r.getDirection().z()
    );
    beta = det3x3(
        a.x() - r.getOrigin().x(), a.x() - c.x(), r.getDirection().x(),
        a.y() - r.getOrigin().y(), a.y() - c.y(), r.getDirection().y(),
        a.z() - r.getOrigin().z(), a.z() - c.z(), r.getDirection().z()
    ) / A;
    gamma = det3x3(
        a.x() - b.x(), a.x() - r.getOrigin().x(), r.getDirection().x(),
        a.y() - b.y(), a.y() - r.getOrigin().y(), r.getDirection().y(),
        a.z() - b.z(), a.z() - r.getOrigin().z(), r.getDirection().z()
    ) / A;
    t = det3x3(
        a.x() - b.x(), a.x() - c.x(), a.x() - r.getOrigin().x(),
        a.y() - b.y(), a.y() - c.y(), a.y() - r.getOrigin().y(),
        a.z() - b.z(), a.z() - c.z(), a.z() - r.getOrigin().z()
    ) / A;
    if (beta + gamma < 1 && beta > 0 && gamma > 0) {
        if (t > tmin && t < h.getT()) {
            h.set(t, material, normal, r);
            return true;
        }
    }
    return false;
}

void Triangle::paint() {
    material->glSetMaterial();
    glBegin(GL_TRIANGLES);
        glNormal3f(normal.x(), normal.y(), normal.z());
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
        glVertex3f(c.x(), c.y(), c.z());
    glEnd();
}

bool Triangle::isTriangle() {
    return true;
}

BoundingBox* Triangle::getTransformedBoundingBox(const Matrix *matrix) const {
    if (!matrix) return boundingBox;
    Vec3f _a = a;
    Vec3f _b = b;
    Vec3f _c = c;
    matrix->Transform(_a);
    matrix->Transform(_b);
    matrix->Transform(_c);

    Vec3f minVertex = Vec3f(min(_a.x(), min(_b.x(), _c.x())),
                            min(_a.y(), min(_b.y(), _c.y())),
                            min(_a.z(), min(_b.z(), _c.z())));
    Vec3f maxVertex = Vec3f(max(_a.x(), max(_b.x(), _c.x())),
                            max(_a.y(), max(_b.y(), _c.y())),
                            max(_a.z(), max(_b.z(), _c.z())));
    return new BoundingBox(minVertex, maxVertex);
}

void Triangle::insertIntoGrid(Grid *g, Matrix *m) {
    BoundingBox *triBoundingBox = boundingBox;
    if (m) {
        triBoundingBox = getTransformedBoundingBox(m);
    }
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

    Vec3f triMin = triBoundingBox->getMin();
    Vec3f triMax = triBoundingBox->getMax();
    int sti = int((triMin - gridMin).x() / xlen);
    int stj = int((triMin - gridMin).y() / ylen);
    int stk = int((triMin - gridMin).z() / zlen);
    int eni = int((triMax - gridMin).x() / xlen);
    int enj = int((triMax - gridMin).y() / ylen);
    int enk = int((triMax - gridMin).z() / zlen);
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
}