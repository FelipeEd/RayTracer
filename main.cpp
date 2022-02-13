#include <iostream>
#include <glm\glm.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

#include "src/FrameBuffer.h"
#include "src/Camera.h"

// A Ray is defined by it starting point + a directon
struct Ray
{
    glm::vec3 origin;
    glm::vec3 dir;

    Ray(glm::vec3 rayOrigin, glm::vec3 direction)
    {
        origin = rayOrigin;
        dir = glm::normalize(direction);
    }

    bool hit_sphere(const glm::vec3 &center, double radius)
    {
        glm::vec3 oc = origin - center;
        auto a = glm::dot(dir, dir);
        auto b = 2.0 * glm::dot(oc, dir);
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        return (discriminant > 0);
    }

    glm::vec3 trace()
    {
        if (hit_sphere(glm::vec3(0, 0, 5), 0.5))
            return glm::vec3(1, 0, 0);

        float t = 0.5f * (dir.y + 1.0f);
        return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
    }
};

int main(int argc, char **argv)
{
    auto start = std::chrono::high_resolution_clock::now();

    //-------------------------------------------------------------------------
    FrameBuffer image;
    Camera camera((float)image.width / (float)image.height);

    glm::vec3 origin(0.0);
    auto horizontal = glm::vec3(camera.viewPortW, 0, 0);
    auto vertical = glm::vec3(0, camera.viewPortH, 0);
    auto lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0, 0, camera.focalLength);

    if (argc > 1)
        std::cerr << "printing " << argv[1] << "\n";
    else
        std::cerr << "printing with no input\n";

    for (int j = 0; j < image.height; j++)
        for (int i = 0; i < image.width; i++)
        {
            float u = float(i) / (image.width - 1);
            float v = float(j) / (image.height - 1);
            Ray r({0.0, 0.0, 0.0}, lower_left_corner + u * horizontal + v * vertical - origin);
            image.at(i, j) = r.trace();
        }

    if (argc > 2)
        image.savePPM(argv[2]);
    else
        image.savePPM("image.ppm");
    //-------------------------------------------------------------------------

    auto stop = std::chrono::high_resolution_clock::now();
    std::cerr << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0f << " s\n";
    return 0;
}