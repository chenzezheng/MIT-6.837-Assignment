#include <limits>
#include "marchingInfo.h"

MarchingInfo::MarchingInfo(int _nx, int _ny, int _nz) {
    nx = _nx, ny = _ny, nz = _nz;
    float inf = std::numeric_limits<float>::max();
    t_current = inf;
    t_next = Vec3f(inf, inf, inf);
}

void MarchingInfo::nextCell() {
    if (t_next.x() <= t_next.y() && t_next.x() <= t_next.z()) {
        i += sign.x();
        t_current = t_next.x();
        t_next += Vec3f(dt.x(), 0, 0);
        normal = Vec3f(-1, 0, 0) * sign.x();
    } else if (t_next.y() <= t_next.x() && t_next.y() <= t_next.z()) {
        j += sign.y();
        t_current = t_next.y();
        t_next += Vec3f(0, dt.y(), 0);
        normal = Vec3f(0, -1, 0) * sign.y();
    } else if (t_next.z() <= t_next.x() && t_next.z() <= t_next.y()) {
        k += sign.z();
        t_current = t_next.z();
        t_next += Vec3f(0, 0, dt.z());
        normal = Vec3f(0, 0, -1) * sign.z();
    }
}

bool MarchingInfo::check() {
    return !(i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz);
}

int MarchingInfo::getIndex() {
    return i + j * nx + k * nx * ny;
}

float MarchingInfo::getT() {
    return t_current;
}

Vec3f MarchingInfo::getNormal() {
    return normal;
}

void MarchingInfo::setT(float _t) {
    t_current = _t;
}

void MarchingInfo::setNormal(Vec3f n) {
    normal = n;
}

void MarchingInfo::setDt(Vec3f _dt) {
    dt = _dt;
}

void MarchingInfo::setTNext(Vec3f _tnext) {
    t_next = _tnext;
}

void MarchingInfo::setSign(Vec3f _sign) {
    sign = _sign;
}

void MarchingInfo::setPosition(int x, int y, int z) {
    i = x;
    j = y;
    k = z;
}