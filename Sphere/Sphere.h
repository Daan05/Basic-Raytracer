#pragma once
#include <glm/glm.hpp>

struct Material
{
public:
	Material()
		: ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0) {};

	double ambient = 0.1;
	double diffuse = 0.9;
	double specular = 0.9;
	double shininess = 200.0;
};

class Sphere
{
public:
	Sphere(double _radius, glm::vec3 _center)
		: radius(_radius), center(_center), color({ 0, 0, 0 }), material(Material()) {}

	double radius;
	glm::vec3 center;
	glm::vec3 color;
	Material material;
};

struct Light_source
{
public:
	Light_source(glm::vec3 _origin, glm::vec3 _intensity)
		: origin(_origin), intensity(_intensity) {}

	glm::vec3 origin;
	glm::vec3 intensity;
};