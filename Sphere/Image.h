#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <iostream>

class Image
{
public:
    Image(int w, int h)
        : width(w), height(h) { Create(); }

    void Create();
    void WritePixel(int row, int column, glm::vec3 color);
    void Print();

    int width;
    int height;

    std::vector<glm::vec3> pixels;
};