#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "ray.h"
#include "hit.h"
#include "grid.h"
#include "vectors.h"
#include "scene_parser.h"

#define TRANSPARENT_SHADOWS false

class RayTracer {
public:
    RayTracer(SceneParser *s, int max_bounces, float cutoff_weight, bool shadows, bool shade_back, int x, int y, int z, bool visualize_grid);
    Vec3f traceRay(Ray &ray, float tmin, int bounces, float weight, Hit &hit) const;
private:
    SceneParser *parser;
    int maxBounces;
    float cutoffWeight;
    bool shadows;
    bool shadeBack;
    Grid *grid;
    int nx, ny, nz;
    bool visualizeGrid;
};

#endif