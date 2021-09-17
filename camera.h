#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ray.h"
#include "vectors.h"

class Camera {
protected:
    Vec3f center;
    Vec3f up;
    Vec3f direction;
    Vec3f horizontal;
public:
    virtual Ray generateRay(Vec2f point) = 0;
    virtual float getTMin() const = 0;
    virtual void glInit(int w, int h) = 0;
    virtual void glPlaceCamera(void) = 0;
    virtual void dollyCamera(float dist) = 0;
    virtual void truckCamera(float dx, float dy) = 0;
    virtual void rotateCamera(float rx, float ry) = 0;
};

class OrthographicCamera : public Camera {
private:
    float size;
public:
    OrthographicCamera(Vec3f &c, Vec3f &d, Vec3f &u, float s);
    Ray generateRay(Vec2f point);
    float getTMin() const;    
    void glInit(int w, int h);
    void glPlaceCamera(void);
    void dollyCamera(float dist);
    void truckCamera(float dx, float dy);
    void rotateCamera(float rx, float ry);
};

class PerspectiveCamera : public Camera {
private:
    float angle;    // radian
public:
    PerspectiveCamera(Vec3f &c, Vec3f &d, Vec3f &u, float a);
    Ray generateRay(Vec2f point);
    float getTMin() const;
    void glInit(int w, int h);
    void glPlaceCamera(void);
    void dollyCamera(float dist);
    void truckCamera(float dx, float dy);
    void rotateCamera(float rx, float ry);
};

#endif