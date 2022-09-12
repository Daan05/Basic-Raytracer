#include "Image.h"

void Image::Create()
{
    glm::vec3 greenish = { double(216.0 / 255.0), double(228.0 / 255.0), double(200.0 / 255.0) };
    for (int i = 0; i < width * height; i++)
    {
        pixels.push_back(greenish);
    }
    std::cout << "pixels: " << pixels.size() << "\n";
}

void Image::WritePixel(int x, int y, glm::vec3 color)
{
    if (0 <= y * width + x && y * width + x < pixels.size() && y >= 0 && x >= 0)
        pixels.at(y * width + x) = color;
    else
    {
        std::cout << "Invalid pixel" << "\n";
        std::cout << x << " " << y << "\n";
    }
}

void Image::Print()
{
    std::ofstream fout("out.ppm");
    fout << "P3\n" << width << " " << height << "\n255\n";
    for (const glm::vec3& pixel : pixels)
    {
        fout << (int)(pixel.x * 255.99) << " " << (int)(pixel.y * 255.99) << " " << (int)(pixel.z * 255.99) << "\n";
    }
}