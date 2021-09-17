#include "rayTracer.h"
#include "group.h"
#include "light.h"
#include "material.h"
#include "rayTree.h"

RayTracer::RayTracer(SceneParser *s, int max_bounces, float cutoff_weight, bool shadows, bool shade_back, int x, int y, int z, bool visualize_grid) {
    parser = s;
    maxBounces = max_bounces;
    cutoffWeight = cutoff_weight;
    shadows = shadows;
    shadeBack = shade_back;
    nx = x, ny = y, nz = z;
    if (nx > 0) {
        grid = new Grid((parser->getGroup())->getBoundingBox(), nx, ny, nz);
        (parser->getGroup())->insertIntoGrid(grid, NULL);
    } else {
        grid = NULL;
    }
    visualizeGrid = visualize_grid;
}

bool reflect(const Material *material, const Ray &ray, const Hit &hit, Vec3f &attenuation, Ray &reflected) {
    if((material->getReflectiveColor()).Length() < 0.0001) return false;
    Vec3f ray_in = ray.getDirection();
    Vec3f normal = hit.getNormal();
    Vec3f ray_out = ray_in - 2.0f * normal.Dot3(ray_in) * normal;
    ray_out.Normalize();
    reflected = Ray(hit.getIntersectionPoint(), ray_out);
    attenuation = material->getReflectiveColor();
    return true;
}


bool refract(const Material *material, const Ray &ray, const Hit &hit, Vec3f &attenuation, Ray &refracted) {
    if((material->getTransparentColor()).Length() < 0.0001) return false;
    Vec3f ray_in = ray.getDirection();
    Vec3f normal = hit.getNormal();
    float ni_over_nt;
    if (ray_in.Dot3(normal) > 0) {
        normal = -1 * normal;
        ni_over_nt = material->getIndexOfRefraction();
    } else {
        ni_over_nt = 1.0f / material->getIndexOfRefraction();
    }
    Vec3f v = ray_in * -1;
    float NoV = normal.Dot3(v);
    float t = 1 - ni_over_nt * ni_over_nt * (1 - NoV * NoV);
    if (t > 0) {
        Vec3f ray_out = (ni_over_nt * NoV - sqrt(t)) * normal - ni_over_nt * v;
        ray_out.Normalize();
        refracted = Ray(hit.getIntersectionPoint(), ray_out);
        attenuation = material->getTransparentColor();
        return true;
    }
    return false;
}

Vec3f RayTracer::traceRay(Ray &ray, float tmin, int bounces, float weight, Hit &hit) const {
    if (bounces > maxBounces) {
        return Vec3f(0, 0, 0);
    }

    if (visualizeGrid) {
        if (grid->intersect(ray, hit, tmin)) {
            Material *material = hit.getMaterial();
            Vec3f intersection = hit.getIntersectionPoint();
            Vec3f color = material->getDiffuseColor() * parser->getAmbientLight();
            for (int k = 0; k < parser->getNumLights(); k ++ ) {
                Light *light = parser->getLight(k);
                Vec3f dir, col;
                float distance;
                light->getIllumination(intersection, dir, col, distance);
                color += material->Shade(ray, hit, dir, col);
            }
            return color;
        } else {
            return parser->getBackgroundColor();
        }
    }

    Group *group = parser->getGroup();
    if (group->intersect(ray, hit, tmin)) {
        assert(hit.getMaterial() != NULL);
        if (bounces == 0) {
            RayTree::SetMainSegment(ray, 0, hit.getT());
        }

        Material *material = hit.getMaterial();
        Vec3f intersection = hit.getIntersectionPoint();        
        float indexOfRefraction = material->getIndexOfRefraction();
        Vec3f normal = hit.getNormal();
        if (normal.Dot3(ray.getDirection()) > 0) {
            if (shadeBack) {
                normal = (-1.0f) * normal;
                indexOfRefraction = 1.0f / indexOfRefraction;
            } else {
                return Vec3f(0, 0, 0);
            }
        }
        
        Vec3f color = material->getDiffuseColor() * parser->getAmbientLight();
        for (int k = 0; k < parser->getNumLights(); k ++ ) {
            Light *light = parser->getLight(k);
            Vec3f dir, col;
            float distance;
            light->getIllumination(intersection, dir, col, distance);
            // Shadows
            Ray shadowRay = Ray(intersection, dir);
            Hit shadowHit = Hit(distance);
            if (shadows) {
                group->intersect(shadowRay, shadowHit, tmin);
                if (shadowHit.getT() >= distance) {
                    color += material->Shade(ray, hit, dir, col);
                }
            } else {
                color += material->Shade(ray, hit, dir, col);
            }
            RayTree::AddShadowSegment(shadowRay, tmin, shadowHit.getT());
        }

        Ray newRay;
        Vec3f attenuation;
        if (weight > cutoffWeight && reflect(material, ray, hit, attenuation, newRay)) {
            Hit reflectedHit;
            color += attenuation * traceRay(newRay, tmin, bounces + 1, weight * attenuation.Length(), reflectedHit);
            RayTree::AddReflectedSegment(newRay, tmin, reflectedHit.getT());
        }
        // Refraction
        if (weight > cutoffWeight && refract(material, ray, hit, attenuation, newRay)) {
            Hit refractedHit;
            color += attenuation * traceRay(newRay, tmin, bounces + 1, weight * attenuation.Length(), refractedHit);
            RayTree::AddTransmittedSegment(newRay, tmin, refractedHit.getT());
        }
        return color;
    }
    return parser->getBackgroundColor();
}