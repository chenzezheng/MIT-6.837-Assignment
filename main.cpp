#include <cstdio>
#include <iostream>
#include <cstring>
#include <cassert>
#include <GL/freeglut.h>
#include "object3d.h"
#include "group.h"
#include "camera.h"
#include "light.h"
#include "image.h"
#include "ray.h"
#include "hit.h"
#include "rayTracer.h"
#include "scene_parser.h"
#include "glCanvas.h"

const float Epsilon = 1e-4;

char *input_file = NULL;
int width = 100;
int height = 100;
char *output_file = NULL;
char *normal_file = NULL;
float depth_min = 0;
float depth_max = 1;
char *depth_file = NULL;
int theta_steps = 0;
int phi_steps = 0;
int max_bounces = 0;
float cutoff_weight = 0;
bool isShadeBack = false;
bool isShadows = false;
bool isGUI = false;
bool isGouraud = false;
int nx, ny, nz;
bool isVisualizeGrid;

SceneParser *parser;

void parseArgs(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i],"-input")) {
            i++; assert (i < argc); 
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-size")) {
            i++; assert (i < argc);
            width = atoi(argv[i]);
            i++; assert (i < argc); 
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++; assert (i < argc); 
            output_file = argv[i];
        } else if (!strcmp(argv[i],"-depth")) {
            i++; assert (i < argc); 
            depth_min = atof(argv[i]);
            i++; assert (i < argc); 
            depth_max = atof(argv[i]);
            i++; assert (i < argc); 
            depth_file = argv[i];
        } else if (!strcmp(argv[i], "-normals")) {
			i++; assert(i < argc);
			normal_file = argv[i];
		} else if (!strcmp(argv[i], "-shade_back")) {
			isShadeBack = true;
		} else if (!strcmp(argv[i], "-shadows")) {
			isShadows = true;
		} else if (!strcmp(argv[i], "-gui")) {
            isGUI = true;
        } else if (!strcmp(argv[i], "-tessellation")) {
            i++; assert(i < argc);
            theta_steps = atoi(argv[i]);
            i++; assert(i < argc);
            phi_steps = atoi(argv[i]);
        } else if (!strcmp(argv[i], "-gouraud")) {
            isGouraud = true;
        } else if (!strcmp(argv[i], "-bounces")) {
            i++;
            assert(i < argc);
            max_bounces = atoi(argv[i]);
        } else if (!strcmp(argv[i], "-weight")) {
            i++;
            assert(i < argc);
            cutoff_weight = atof(argv[i]);
        } else if (!strcmp(argv[i], "-grid")) {
            i++;
            assert(i < argc);
            nx = atoi(argv[i]);
            i++;
            assert(i < argc);
            ny = atoi(argv[i]);
            i++;
            assert(i < argc);
            nz = atoi(argv[i]);
        } else if (!strcmp(argv[i], "-visualize_grid")) {
            isVisualizeGrid = true;
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }
}

Vec3f CalcDepthColor(float depth_min, float depth_max, float depth) {
    float color = (depth_max - depth) / (depth_max - depth_min);
    return Vec3f(color, color, color);
}

Vec3f CalcNormalColor(const Vec3f &normal) {
    return Vec3f(abs(normal.x()), abs(normal.y()), abs(normal.z()));
}

void render() {
    RayTracer rayTracer = RayTracer(parser, max_bounces, cutoff_weight, isShadows, isShadeBack, nx, ny, nz, isVisualizeGrid);
    Camera *camera = parser->getCamera();
    Image outputImg = Image(width, height);
    outputImg.SetAllPixels(parser->getBackgroundColor());

    for (int i = 0; i < width; i ++ ) {
        for (int j = 0; j < height; j ++ ) {
            Vec2f point = Vec2f((float)i / width, (float)j / height);
            Ray ray = camera->generateRay(point);
            Hit hit;
            Vec3f color = rayTracer.traceRay(ray, Epsilon, 0, 1.0, hit);
            outputImg.SetPixel(i, j, color);
        }
    }
    if (output_file) {
        outputImg.SaveTGA(output_file);
    }
}

void traceRay(float x, float y) {
    RayTracer rayTracer = RayTracer(parser, max_bounces, cutoff_weight, isShadows, isShadeBack, nx, ny, nz, isVisualizeGrid);
    Vec2f point = Vec2f(x, y);
    Ray ray = (parser->getCamera())->generateRay(point);
    Hit hit;
    Vec3f color = rayTracer.traceRay(ray, Epsilon, 0, 1.0, hit);
}

int main(int argc, char *argv[]) {
    parseArgs(argc, argv);
    parser = new SceneParser(input_file);
    Grid *canvasGrid = NULL;
    if (nx > 0) {
        canvasGrid = new Grid((parser->getGroup())->getBoundingBox(), nx, ny, nz);
        (parser->getGroup())->insertIntoGrid(canvasGrid, NULL);
    }
    if (isGUI) {
        glutInit(&argc, argv);
        GLCanvas glCanvas;
        glCanvas.initialize(parser, render, traceRay, canvasGrid, isVisualizeGrid);
    } else {
        render();
    }
    return 0;
}

