#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>

namespace Raytracer148 {
struct Ray {
  Eigen::Vector3d origin, direction;
  int bounce = 0;
  
};

class Shape;

static const double infinity = std::numeric_limits<double>::max();

struct HitRecord {
	Eigen::Vector3d position, normal, color, center;
	double t;					// distance
	const Shape* object = nullptr;
  
};
enum class ObjectType { diffuseObject, reflectiveObject};
class Shape {
public:
	virtual ~Shape(){}
	virtual HitRecord intersect(const Ray &ray) = 0;
	Eigen::Vector3d c;
	ObjectType objectType = ObjectType::diffuseObject;
};


}

#endif
