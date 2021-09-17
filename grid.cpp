#include "grid.h"

Grid::Grid(BoundingBox *bb, int nx, int ny, int nz) : nx(nx), ny(ny), nz(nz) {
    boundingBox = bb;
    for (int i = 0; i < nx * ny * nz; i ++ ) {
        opaque.push_back(new Object3DVector());
    }
    for (int i = 0; i < 8; i ++ ) {
        int b = (~i) & 1;
        int g = ((~i) >> 1) & 1;
        int r = ((~i) >> 2) & 1;
        indicates[i] = new PhongMaterial(Vec3f(r, g, b));
    }
}

Grid::~Grid() {
    delete &opaque;
}

void Grid::initializeRayMarch(MarchingInfo &info, const Ray &r, float tmin) const {
    Vec3f gridMin = boundingBox->getMin();
    Vec3f gridMax = boundingBox->getMax();
    Vec3f gridLength = gridMax - gridMin;
    float xlen = gridLength.x() / float(nx);
    float ylen = gridLength.y() / float(ny);
    float zlen = gridLength.z() / float(nz);

    Vec3f ori = r.getOrigin();
    Vec3f dir = r.getDirection();
    
    float dt_x = abs(xlen / dir.x());
    float dt_y = abs(ylen / dir.y());
    float dt_z = abs(zlen / dir.z());
    info.setDt(Vec3f(dt_x, dt_y, dt_z));
    
    float sign_x = dir.x() > 0 ? 1 : -1;
    float sign_y = dir.y() > 0 ? 1 : -1;
    float sign_z = dir.z() > 0 ? 1 : -1;
    info.setSign(Vec3f(sign_x, sign_y, sign_z));

    Vec3f t1 = gridMin - ori;
    t1.Divide(dir);
    Vec3f t2 = gridMax - ori;
    t2.Divide(dir);
    Vec3f vec_min = Vec3f(min(t1.x(), t2.x()), min(t1.y(), t2.y()), min(t1.z(), t2.z()));
    Vec3f vec_max = Vec3f(max(t1.x(), t2.x()), max(t1.y(), t2.y()), max(t1.z(), t2.z()));
    float t_near = max(vec_min.x(), max(vec_min.y(), vec_min.z()));
    float t_far = min(vec_max.x(), min(vec_max.y(), vec_max.z()));
    if (t_near >= t_far || t_far <= tmin) return;
    if (t_near < tmin) {
        while (vec_min.x() > -INFINITY && vec_min.x() < tmin) vec_min += Vec3f(dt_x, 0, 0);
        while (vec_min.y() > -INFINITY && vec_min.y() < tmin) vec_min += Vec3f(0, dt_y, 0);
        while (vec_min.z() > -INFINITY && vec_min.z() < tmin) vec_min += Vec3f(0, 0, dt_z);
        if (vec_min.x() < tmin) vec_min = Vec3f(INFINITY, vec_min.y(), vec_min.z());
        if (vec_min.y() < tmin) vec_min = Vec3f(vec_min.x(), INFINITY, vec_min.z());
        if (vec_min.z() < tmin) vec_min = Vec3f(vec_min.x(), vec_min.y(), INFINITY);
        t_near = min(vec_min.x(), min(vec_min.y(), vec_min.z()));
        info.setT(t_near);
        if (vec_min.x() <= vec_min.y() && vec_min.x() <= vec_min.z()) {
            info.setNormal(Vec3f(-1, 0, 0) * sign_x);
            vec_min += Vec3f(dt_x, 0, 0);
            info.setTNext(vec_min);
        } else if (vec_min.y() <= vec_min.x() && vec_min.y() <= vec_min.z()) {
            info.setNormal(Vec3f(0, -1, 0) * sign_y);
            vec_min += Vec3f(0, dt_y, 0);
            info.setTNext(vec_min);
        } else {
            info.setNormal(Vec3f(0, 0, -1) * sign_z);
            vec_min += Vec3f(0, 0, dt_z);
            info.setTNext(vec_min);
        }
    } else {
        info.setT(t_near);
        if (t_near == vec_min.x()) {
            info.setNormal(Vec3f(-1, 0, 0) * sign_x);
        } else if (t_near == vec_min.y()) {
            info.setNormal(Vec3f(0, -1, 0) * sign_y);
        } else {
            info.setNormal(Vec3f(0, 0, -1) * sign_z);
        }
        while (vec_min.x() > -INFINITY && vec_min.x() <= t_near) vec_min += Vec3f(dt_x, 0, 0);
        while (vec_min.y() > -INFINITY && vec_min.y() <= t_near) vec_min += Vec3f(0, dt_y, 0);
        while (vec_min.z() > -INFINITY && vec_min.z() <= t_near) vec_min += Vec3f(0, 0, dt_z);
        if (vec_min.x() < tmin) vec_min = Vec3f(INFINITY, vec_min.y(), vec_min.z());
        if (vec_min.y() < tmin) vec_min = Vec3f(vec_min.x(), INFINITY, vec_min.z());
        if (vec_min.z() < tmin) vec_min = Vec3f(vec_min.x(), vec_min.y(), INFINITY);
        info.setTNext(vec_min);
    }

    Vec3f pos = r.pointAtParameter(t_near) - gridMin;
    int i = int(pos.x() / xlen);
    int j = int(pos.y() / ylen);
    int k = int(pos.z() / zlen);
    if (i == nx && sign_x < 0) i -- ;
    if (j == ny && sign_y < 0) j -- ;
    if (k == nz && sign_z < 0) k -- ;
    info.setPosition(i, j, k);
}

bool Grid::intersect(const Ray &r, Hit &h, float tmin) {
    Object3DVector *temp = opaque[nx*ny*nz-1];



    MarchingInfo info = MarchingInfo(nx, ny, nz);
    initializeRayMarch(info, r, tmin);
    if (info.getT() >= h.getT()) return false;
    while (info.check()) {
        int index = info.getIndex();
        Object3DVector *objects = opaque[index];
        if (objects->getNumObjects() == 0) {
            info.nextCell();
            continue;
        }
        PhongMaterial *m = indicates[min(objects->getNumObjects(), 8) - 1];
        h.set(info.getT(), m, info.getNormal(), r);
        return true;
    }
    return false;
}

void Grid::paint() {
    Vec3f gridMin = boundingBox->getMin();
    Vec3f gridMax = boundingBox->getMax();
    Vec3f gridLength = gridMax - gridMin;
    float xlen = gridLength.x() / float(nx);
    float ylen = gridLength.y() / float(ny);
    float zlen = gridLength.z() / float(nz);

    for (int i = 0; i < nx; i ++ ) {
        for (int j = 0; j < ny; j ++ ) {
            for (int k = 0; k < nz; k ++ ) {
                Object3DVector *objects = getObjectVector(Vec3f(i, j, k));
                if (objects->getNumObjects() == 0) continue;
                Vec3f a = gridMin + Vec3f(i * xlen, j * ylen, k * zlen);
                Vec3f b = gridMin + Vec3f((i + 1) * xlen, j * ylen, k * zlen);
                Vec3f c = gridMin + Vec3f((i + 1) * xlen, (j + 1) * ylen, k * zlen);
                Vec3f d = gridMin + Vec3f(i * xlen, (j + 1) * ylen, k * zlen);
                Vec3f e = gridMin + Vec3f(i * xlen, j * ylen, (k + 1) * zlen);
                Vec3f f = gridMin + Vec3f((i + 1) * xlen, j * ylen, (k + 1) * zlen);
                Vec3f g = gridMin + Vec3f((i + 1) * xlen, (j + 1) * ylen, (k + 1) * zlen);
                Vec3f h = gridMin + Vec3f(i * xlen, (j + 1) * ylen, (k + 1) * zlen);
                PhongMaterial *color = indicates[min(objects->getNumObjects(), 8) - 1];
                color->glSetMaterial();
                glBegin(GL_QUADS);
                    glNormal3f(0, 0, -1);
                    glVertex3f(a.x(), a.y(), a.z());
                    glVertex3f(b.x(), b.y(), b.z());
                    glVertex3f(c.x(), c.y(), c.z());
                    glVertex3f(d.x(), d.y(), d.z());
                    glNormal3f(0, 0, 1);
                    glVertex3f(e.x(), e.y(), e.z());
                    glVertex3f(f.x(), f.y(), f.z());
                    glVertex3f(g.x(), g.y(), g.z());
                    glVertex3f(h.x(), h.y(), h.z());
                    glNormal3f(1, 0, 0);
                    glVertex3f(b.x(), b.y(), b.z());
                    glVertex3f(c.x(), c.y(), c.z());
                    glVertex3f(g.x(), g.y(), g.z());
                    glVertex3f(f.x(), f.y(), f.z());
                    glNormal3f(-1, 0, 0);
                    glVertex3f(a.x(), a.y(), a.z());
                    glVertex3f(d.x(), d.y(), d.z());
                    glVertex3f(h.x(), h.y(), h.z());
                    glVertex3f(e.x(), e.y(), e.z());
                    glNormal3f(0, -1, 0);
                    glVertex3f(a.x(), a.y(), a.z());
                    glVertex3f(b.x(), b.y(), b.z());
                    glVertex3f(f.x(), f.y(), f.z());
                    glVertex3f(e.x(), e.y(), e.z());
                    glNormal3f(0, 1, 0);
                    glVertex3f(c.x(), c.y(), c.z());
                    glVertex3f(d.x(), d.y(), d.z());
                    glVertex3f(h.x(), h.y(), h.z());
                    glVertex3f(g.x(), g.y(), g.z());
                glEnd();
            }
        }
    }
}

Object3DVector* Grid::getObjectVector(Vec3f id) {
    int index = id.x() + id.y() * nx + id.z() * nx * ny;
    return opaque[index];
}

void Grid::addObject(int index, Object3D *obj) {
    opaque[index]->addObject(obj);
}

void Grid::addObject(Vec3f id, Object3D *obj) {
    int index = id.x() + id.y() * nx + id.z() * nx * ny;
    opaque[index]->addObject(obj);
}

Vec3f Grid::getNumCells() {
    return Vec3f(nx, ny, nz);
}