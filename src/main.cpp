#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Disk.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);                             // image size

    Scene scene;                                    // create scene

    Vector3d center;
    Vector3d color;

    int problem;
    problem = 4;                                    // current prolem to render
    scene.problem(problem);                         // set light position based on problem number

    center[0] = -1.4;                               // x coord
    center[1] = 0;                                  // y coord
    center[2] = 4;                                  // z coord
    color = { 1, 0, 0 };
    //scene.addShape(new Sphere(center, 2, color));   // add shape and radius

    center[0] = -1.5;
    center[1] = 1.25;
    center[2] = 2.5;
    color = { 1, 1, 0 };
    //scene.addShape(new Sphere(center, .5, color));

    center[0] = 1;
    center[1] = -1;
    center[2] = 2;
    color = { 0, 1, 0 };
    //scene.addShape(new Sphere(center, .35, color));

    // problem 1 adds more primitive shapes to a simple scene 
    if (problem == 1)
    {
        center[0] = 0;
        center[1] = 0;
        center[2] = 3;
        color = { 1, 1, 1 };            // ring
        scene.addShape(new Disk(center, 1.05, color, Disk::ring));

        center[0] = 0;
        center[1] = 0;
        center[2] = 2.5;
        color = { 1, 1, 1 };            // center sphere
        scene.addShape(new Sphere(center, .6, color, "diffuse"));
    }

    // problem 2 adds phong shading to simple shapes
    if (problem == 2)
    {
        center[0] = -.35;
        center[1] = .4;
        center[2] = 1;
        color = { .07, .34, .43 };    // left sphere
        scene.addShape(new Sphere(center, .3, color, "diffuse"));

        center[0] = .4;
        center[1] = -.4;
        center[2] = 1;
        color = { .95, .78, .47 };    // right sphere
        scene.addShape(new Sphere(center, .3, color, "diffuse"));
    }

    // problem 3 adds support for shadows to the scene
    if (problem == 3)
    {
        center[0] = 0;
        center[1] = 0;
        center[2] = 3;
        color = { .55, .70, .43 };    // background disk
        scene.addShape(new Disk(center, 1.05, color, Disk::disk));

        center[0] = -.4;
        center[1] = -.1;
        center[2] = 1;
        color = { .82, .40, .0 };    // left sphere
        scene.addShape(new Sphere(center, .15, color, "diffuse"));

        center[0] = .4;
        center[1] = -.1;
        center[2] = 1;
        color = { .11, .15, .30 };    // right sphere
        scene.addShape(new Sphere(center, .15, color, "diffuse"));

        center[0] = 0;
        center[1] = .5;
        center[2] = 1;
        color = { .76, .35, .38 };    // top sphere
        scene.addShape(new Sphere(center, .15, color, "diffuse"));

    }

    // problem 4 adds more shapes and support for mirrored surfaces that reflect light
    if (problem == 4)
    {
        center[0] = -.95;
        center[1] = 0;
        center[2] = 1.25;
        color = { .99, .15, .15 };    // red
        scene.addShape(new Sphere(center, .15, color, "diffuse"));

        center[0] = -.45;
        center[1] = -0.69;
        center[2] = 1.25;
        color = { .97, .33, 0.0 };    // orange
        scene.addShape(new Sphere(center, .15, color, "diffuse"));

        center[0] = 0.45;
        center[1] = -0.69;
        center[2] = 1.25;
        color = { .45, .73, .06 };    // green
        scene.addShape(new Sphere(center, .15, color, "diffuse"));

        center[0] = .95;
        center[1] = 0;
        center[2] = 1.25;
        color = { .0, .49, .97 };    // blue
        scene.addShape(new Sphere(center, .15, color, "diffuse"));

        center[0] = 0;
        center[1] = 0;
        center[2] = 1;
        color = { .31, .64, .57 };    // blue (middle)
        scene.addShape(new Sphere(center, .12, color, "diffuse"));

        center[0] = 0;
        center[1] = 0;
        center[2] = 3;
        color = { 1, 1, .1 };          // ring
        scene.addShape(new Disk(center, 1.0555, color, Disk::ring));

        center[0] = 0;
        center[1] = 2;
        center[2] = 2;
        color = { 1, 1, 0 };    // sphere mirror
        scene.addShape(new Sphere(center, 1.6, color, "reflective"));

        center[0] = 0;
        center[1] = -3.55;
        center[2] = 0;
        color = { .57, .43, .42 }; // foreground sphere
        scene.addShape(new Sphere(center, 2.75, color, "diffuse"));
    }


    scene.render(im);                               // render image
    im.writePNG("test.png");                        // image name and path

    return 0;
}
