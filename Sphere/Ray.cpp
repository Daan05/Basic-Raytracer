#include "Ray.h"

std::vector<Intersection> intersect(Ray r, std::vector<Sphere> objects)
{
	std::vector<Intersection> intersections = {};
	for (const Sphere& object : objects)
	{
		glm::vec3 sphere_to_ray = r.origin - object.center;
		double a = glm::dot(r.direction, r.direction);
		double b = 2 * glm::dot(r.direction, sphere_to_ray);
		double c = glm::dot(sphere_to_ray, sphere_to_ray) - object.radius * object.radius;
		double discriminant = b * b - 4 * a * c;

		if (discriminant >= 0)
		{
			Intersection t1((-b - sqrt(discriminant)) / (2 * a), object);
			Intersection t2((-b + sqrt(discriminant)) / (2 * a), object);

			intersections.push_back(t1);
			intersections.push_back(t2);
		}
	}

	sort(intersections.begin(), intersections.end(), [](const Intersection& lhs, const Intersection& rhs) { return lhs.t < rhs.t&& lhs.t > 0; });

	return intersections;
}

glm::vec3 calc_lighting(Sphere s, Light_source light, glm::vec3 point, glm::vec3 eyev, glm::vec3 normalv)
{
	glm::vec3 black = { 0, 0, 0 };

	glm::vec3 ambient = black;
	glm::vec3 diffuse = black;
	glm::vec3 specular = black;

	glm::vec3 effective_color = s.color;// + light.intensity;
	glm::vec3 lightv = glm::normalize(light.origin - point);
	ambient = { effective_color.r * s.material.ambient, effective_color.g * s.material.ambient, effective_color.b * s.material.ambient };
	double light_dot_normal = glm::dot(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = black;
		specular = black;
	}
	else
	{
		diffuse = { effective_color.r * s.material.diffuse * light_dot_normal, effective_color.g * s.material.diffuse * light_dot_normal, effective_color.b * s.material.diffuse * light_dot_normal };
		glm::vec3 reflectv = glm::reflect(-lightv, normalv);
		double reflect_dot_eye = glm::dot(reflectv, eyev);
		if (reflect_dot_eye <= 0)
		{
			specular = black;
		}
		else
		{
			double factor = pow(reflect_dot_eye, s.material.shininess);
			specular = { light.intensity.r * s.material.specular * factor, light.intensity.g * s.material.specular * factor, light.intensity.b * s.material.specular * factor };
		}
	}
	return ambient + diffuse + specular;
}