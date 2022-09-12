#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

#include "Sphere.h"

struct Ray
{
public:
	Ray(glm::vec3 _origin, glm::vec3 _direction)
		: origin(_origin), direction(_direction) {};

	glm::vec3 origin;
	glm::vec3 direction;
};

struct Intersection
{
public:
	Intersection(double _t, Sphere _object)
		: t(_t), object(_object) {}

	double t;
	Sphere object;
};

std::vector<Intersection> intersect(Ray r, std::vector<Sphere> objects);

glm::vec3 calc_lighting(Sphere s, Light_source light, glm::vec3 point, glm::vec3 eyev, glm::vec3 normalv);