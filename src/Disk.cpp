#include "Disk.h"
#include <limits>
#include <math.h>
#include <iostream>     // delete after troubleshoot



using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Disk::intersect(const Ray& ray) {
    HitRecord result;
    result.t = -1;
    Eigen::Vector3d numerator;

    numerator = (c - (ray.origin + ray.direction));
    double denominator = ray.direction.dot(ray.direction.normalized());     // d.N

    double t = -1;
    if (denominator > 0) t = numerator.dot(numerator.normalized()) / denominator; // dont divide by 0

    if (t < numeric_limits<double>::epsilon()) return result; // no hit

    // disk or ring instead of plane
    if (t >= numeric_limits<double>::epsilon())
    {
        Eigen::Vector3d p = ray.origin + ray.direction * t;
        Eigen::Vector3d v = p - c;
        double d2 = v.dot(v);
        if (sqrt(d2) <= d*2)
        {
            if (type == disk)               // if type is disk
            {
                result.t = t;
                result.position = ray.origin + result.t * ray.direction;    // (o + td)
                result.normal = (result.position - c).normalized();         // (o + td - p0).N
            }
            else if (type == ring)
            {
                if (sqrt(d2) >= d * 1.3675) // if type is ring
                {
                    result.t = t;
                    result.position = ray.origin + result.t * ray.direction;    // (o + td)
                    result.normal = (result.position - c).normalized();         // (o + td - p0).N
                }
            }
        }
    }

    // uncomment for plane
    //if (t >= numeric_limits<double>::epsilon()) result.t = t;  // hit
    //result.position = ray.origin + result.t * ray.direction;    // (o + td)
    //result.normal = (result.position - c).normalized();         // (o + td - p0).N

    result.center = c;                      // record center of object
    result.color = this->color;             // add color

    return result;
}

