#ifndef _MARCHINGINFO_H_
#define _MARCHINGINFO_H_

#include "vectors.h"

class MarchingInfo {
public:
    MarchingInfo(int _nx, int _ny, int _nz);
    void nextCell();
    bool check();
    int getIndex();

    //ACCESSOR
    float getT();
    Vec3f getNormal();
    void setT(float _t);
    void setNormal(Vec3f n);
    void setDt(Vec3f _dt);
    void setTNext(Vec3f _tnext);
    void setSign(Vec3f _sign);
    void setPosition(int x, int y, int z);
private:
    int nx, ny, nz;
    float t_current;
    int i, j, k;
    Vec3f t_next;
    Vec3f dt;
    Vec3f sign;
    Vec3f normal;
};

#endif