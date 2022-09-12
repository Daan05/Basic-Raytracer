//--------------------------------------------
// Entry point
//--------------------------------------------

#include <iostream>
#include <glm/glm.hpp>

#include "Image.h"
#include "Sphere.h"
#include "Ray.h"
#include "World.h"

int main()
{
    clock_t time_req;
    time_req = clock();

    int canvas_x = 800*3;
    int canvas_y = 500*3;
    Image image(canvas_x, canvas_y);
    //--------------------------------------------

    World w;

    Light_source light({ -20, 20, -20 }, { 1, 1, 1 });
    w.lights.push_back(light);

    Sphere shape1(1, { 1, 0.3, -0.5 });
    shape1.color = { 0, 0.8, 0 };
    Sphere shape2(1, { -0.7, -0.5, 0 });
    shape2.color = { 0.8, 0, 0 };

    w.objects.push_back(shape1);
    w.objects.push_back(shape2);
    

    glm::vec3 ray_origin = { 0, 0, -30 };
    double wall_z = 10;
    double wall_size_x = 8;
    double wall_size_y = 5;

    double pixel_size_x = wall_size_x / canvas_x;
    double pixel_size_y = wall_size_y / canvas_y;
    double half_x = wall_size_x / 2;
    double half_y = wall_size_y / 2;

    for (int y = 0; y < canvas_y; y++)
    {
        double world_y = half_y - pixel_size_y * y;
        for (int x = 0; x < canvas_x; x++)
        {
            double world_x = -half_x + pixel_size_x * x;
            glm::vec3 position_v = { world_x, world_y, wall_z };
            Ray ray(ray_origin, glm::normalize(position_v - ray_origin));
            std::vector<Intersection> xs = intersect(ray, w.objects);
            if (xs.size() > 0)
            {
                Sphere object = xs.at(0).object;
                glm::vec3 t = { xs.at(0).t, xs.at(0).t, xs.at(0).t };
                glm::vec3 point = ray.origin + ray.direction * t;
                glm::vec3 normal = point - object.center;

                image.WritePixel(x, y, calc_lighting(object, w.lights.at(0), point, -ray.direction, normal));
            }
        }
    }

    //--------------------------------------------

    std::cout << "calculations finished in " << ((float)clock() - (float)time_req) / CLOCKS_PER_SEC << " seconds" << "\n";

    image.Print();
    time_req = clock() - time_req;

    std::cout << "Program finished in " << (float)time_req / CLOCKS_PER_SEC << " seconds" << "\n";
    return 0;
}