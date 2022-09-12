#pragma once
#include <vector>

#include "Sphere.h"

class World
{
public:
	World()
		: objects({}), lights({}) {}

	std::vector<Sphere> objects;
	std::vector<Light_source> lights;
};