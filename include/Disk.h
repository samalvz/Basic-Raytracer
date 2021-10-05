#ifndef DISK_H
#define DISK_H

#include "Shape.h"

namespace Raytracer148 {
    class Disk : public Shape {
    public:
        enum type {plane, disk, ring};
        Disk(Eigen::Vector3d& center, double diameter, Eigen::Vector3d color, type type) : c(center), d(diameter), color(color), type(type) {}

        virtual HitRecord intersect(const Ray& ray);

    private:
        Eigen::Vector3d c;
        Eigen::Vector3d color;
        double d;
        type type;
    };
}

#endif