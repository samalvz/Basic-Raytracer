#include "Sphere.h"
#include <limits>
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Sphere::intersect(const Ray &ray) {
    HitRecord result;
    result.t = -1;

    // set up intersection system as at^2+bt+c
    double at = ray.direction.squaredNorm();
    double bt = 2 * ray.direction.dot(ray.origin - c);      
    double ct = (ray.origin - c).squaredNorm() - r * r;     // point on sphere

    double discriminant = bt * bt - 4 * at * ct;

    if (discriminant < numeric_limits<double>::epsilon()) return result; // no hit!

    double t0 = (-bt - sqrt(discriminant)) / (2 * at);
    double t1 = (-bt + sqrt(discriminant)) / (2 * at);

    if (t1 < numeric_limits<double>::epsilon()) return result;  // no hit!


    if (t0 > numeric_limits<double>::epsilon()) result.t = t0;  // use closer hit if it's in front
    else result.t = t1;

    result.position = ray.origin + result.t * ray.direction;    // point along ray
    result.normal = (result.position - c).normalized();

    result.center = c;
    result.color = this->color;
    if (objType == "diffuse") objectType = ObjectType::diffuseObject;
    else if (objType == "reflective") objectType = ObjectType::reflectiveObject;

    return result;
}



