#ifndef SCENE_H
#define SCENE_H

#include "Shape.h"
#include "Image.h"
#include <vector>
#include <limits>

using namespace Eigen;

namespace Raytracer148 {
class Scene {
public:
  Scene() {
    // default light position if location is not specified
    lightPos[0] = 3;
    lightPos[1] = 3;
    lightPos[2] = 0;

    // light color and light intensity
    lightColor[0] = lightColor[1] = lightColor[2] = 1;
    lightIntensity[0] = lightIntensity[1] = lightIntensity[2] = .9;
  }

  virtual ~Scene() {
    for (unsigned int i = 0; i < shapes.size(); i++)
      delete shapes[i];
    shapes.resize(0);
  }


  void addShape(Shape *s) { shapes.push_back(s); }
  HitRecord closestHit(const Ray &ray);
  Eigen::Vector3d trace(const Ray &ray, int bounces);
  HitRecord shade(const Ray& ray, Vector3d point, Vector3d direction, Vector3d color);
  void render(Image &image);
  void problem(int problem);


private:
  std::vector<Shape*> shapes;
  Eigen::Vector3d lightPos;
  Eigen::Vector3d lightColor;
  Eigen::Vector3d lightIntensity;
  const int MAX_BOUNCES = 2;
};
}

#endif
