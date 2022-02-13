#include <iostream>
#include <glm\glm.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;

    Ray()
    {
        origin = glm::vec3(0.0);
        direction = glm::vec3(0.0, 0.0, 1.0);
    }
};

struct Image
{
    unsigned int width, height;
    std::vector<glm::vec3> data;

    Image(int w = 800, int h = 600)
    {
        width = w;
        height = h;
        data.resize(height * width);

        for (int i = 0; i < width * height; i++)
        {
            data[i] = glm::vec3(1.0, 0.0, 0.0);
        }
    }

    void savePPM(const char *fileName)
    {
        std::ofstream ofs(fileName, std::ios_base::out | std::ios_base::binary);
        ofs << "P6" << std::endl
            << width << ' ' << height << std::endl
            << "255" << std::endl;

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                ofs << (char)(data[i * height + j].r * 255) << (char)(data[i * height + j].g * 255) << (char)(data[i * height + j].b * 255);

        ofs.close();
    }
};

int main(int argc, char **argv)
{
    Ray raio;
    Image testImage;

    std::cerr << "printing ppm\n";
    auto start = std::chrono::high_resolution_clock::now();

    testImage.savePPM("image.ppm");

    auto stop = std::chrono::high_resolution_clock::now();

    std::cerr << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0f << " s\n";

    return 0;
}