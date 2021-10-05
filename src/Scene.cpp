#include "Scene.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

// reflect method, as detailed from openGL documentation
Vector3d reflect(const Vector3d I, const Vector3d N)
{
    Eigen::Vector3d reflect = I - 2 * I.dot(N) * N;
    return reflect;
}

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    result.object = nullptr;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);

        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            r.object = shapes[i];
            result = r;
            foundSomething = true;
        }
    }
    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int depth) {

    Vector3d result;                            // rgb 
    result = { 0.07, .19, .28 };                // background
    //result[0] = result[1] = result[2] = 0;    // background for problems 1 and 2
    if (depth > MAX_BOUNCES) return result;

    HitRecord r = closestHit(ray);

    Vector3d hitPoint = ray.origin + ray.direction * r.t;
    Vector3d hitNormal = hitPoint - r.center;

    double reflectBias = 0.005;            // reflect bias
    double shadeBias = 0.008;              // shade bias
    double ambientStrength = 0.3;          // ambience strength
    double specularStrength = 0.022;        // specular strength
    //specularStrength = 0.1;                 // specular strength for problem 2 and 3
    Vector3d viewPos = { 0, 0, 0 };

    if (r.t < numeric_limits<double>::epsilon()) return result; // return background color

    Vector3d lightDirection = (lightPos - r.position).normalized();
    double dot = lightDirection.dot(r.normal);
    if (dot < 0) dot = 0;

    Vector3d final = { 0, 0, 0 };
    
    switch (r.object->objectType)
    {
        case ObjectType::diffuseObject:
        {
            HitRecord shadow;
            shadow = shade(ray, hitPoint + hitNormal * shadeBias , lightDirection, r.color);
            double colorSum = shadow.color[0] + shadow.color[1] + shadow.color[2];
            //shadow = r; // uncomment for problems 1 and 2

            // --- PHONG SHADING ----------------------------------
                // ambient
            Vector3d ambient = shadow.color * ambientStrength;
            // diffuse
            Vector3d diffuse = shadow.color * max(0.0, r.normal.dot(lightDirection));
            // specular
            Vector3d ref = reflect(-lightDirection, r.normal);
            Vector3d specular = lightIntensity * pow(max(ref.dot(-ray.direction), 0.0), 2);
            if (colorSum == 0)specular[0] = specular[1] = specular[2] = 0;

            // final color
            final += ambient + diffuse + specular * specularStrength;
            break;
        }
        case ObjectType::reflectiveObject:
        {
            Ray reflection;
            Vector3d reflectDir = reflect(ray.direction, hitNormal);
            reflection.origin = hitPoint + hitNormal * shadeBias;
            reflection.direction = reflectDir;

            final += 0.9 * trace(reflection, depth++);
            break;
        }
        default:
        {
            break;
        }
    }
    return final;
}


HitRecord Scene::shade(const Ray& ray, Vector3d point, Vector3d direction, Vector3d color)
{
    // shadow ray with hitPoint as origin and direction towards lightsource
    Ray shadRay;
    shadRay.origin = point;
    shadRay.direction = direction.normalized();
    HitRecord shadow = closestHit(shadRay);
    Vector3d newColor;

    // if nothing is hit there is no shadow
    if (shadow.t <= -1)
    {
        shadow.color = color;
    }
    // if something is hit, there is a shadow
    else
    {
        shadow.normal = shadRay.direction;
        shadow.position = (direction - point);
        shadow.color = { 0, 0, 0 };
    } 
    return shadow;
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay, 0);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}

// set light position based on problem number
void Scene::problem(int problem)
{
    switch (problem)
    {
        case 1:
        {
            lightPos[0] = lightPos[1] = 4;
            lightPos[2] = -5;
            break;
        }
        case 2:
        {
            lightPos[0] = 1;
            lightPos[1] = 1;
            lightPos[2] = .25;
            break;
        }
        case 3:
        {
            lightPos[0] = 2;
            lightPos[1] = -2;
            lightPos[2] = -2;
            break;
        }
        case 4:
        {
            lightPos[0] = 1;
            lightPos[1] = 1;
            lightPos[2] = -1;
            break;
        }
        default:
            break;
    }
}
