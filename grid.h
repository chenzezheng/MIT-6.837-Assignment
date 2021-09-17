#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include "material.h"
#include "object3d.h"
#include "marchingInfo.h"
#include "object3dvector.h"

class Grid : public Object3D {
public:
    Grid(BoundingBox *bb, int nx, int ny, int nz);
    ~Grid();
    void initializeRayMarch(MarchingInfo &info, const Ray &r, float tmin) const;
    bool intersect(const Ray &r, Hit &h, float tmin);
    void paint();
    Object3DVector* getObjectVector(Vec3f id);
    void addObject(int index, Object3D *obj);
    void addObject(Vec3f id, Object3D *obj);
    Vec3f getNumCells();
private:
    int nx, ny, nz;
    vector< Object3DVector* > opaque;
    PhongMaterial *indicates[8];
};

#endif