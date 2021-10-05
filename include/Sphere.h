#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include <string>
namespace Raytracer148 {
class Sphere : public Shape {
public:
    Sphere(Eigen::Vector3d &center, double radius, Eigen::Vector3d &color, std::string objType) : c(center), r(radius), color(color), objType(objType) {}

    virtual HitRecord intersect(const Ray &ray);
private:
    Eigen::Vector3d c;
    Eigen::Vector3d color;
    double r;
    std::string objType;

};
}

#endif
