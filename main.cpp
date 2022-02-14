#include <iostream>
#include <glm\glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <memory>

#include "src/RayTracer.h"
#include "src/Scene.h"
#include "src/Sphere.h"

struct input
{
    // Camera
    glm::vec3 camPos;
    glm::vec3 cmlookAt;
    glm::vec3 camNormal;
    float camFOV;

    // Lights
    std::vector<Light> lights; // ! The first one is ambient light
    // TODO Pigmentos
};

int main(int argc, char **argv)
{
    auto start = std::chrono::high_resolution_clock::now();

    //-------------------------------------------------------------------------
    Scene scene;
    RayTracer renderer;
    int nframes = 10;

    for (int i = 0; i < 5; i++)
        scene.add(std::make_shared<Sphere>(Sphere({-4.0f + i * 2, 1.0f, 0.0f}, 1.0f)));

    for (int i = 0; i < 5; i++)
        scene.add(std::make_shared<Sphere>(Sphere({0.0f, 1.0f, -4.0f + i * 2}, 1.0f)));

    scene.add(std::make_shared<Sphere>(Sphere({0.0f, -100.0f, 0.0f}, 100.0f)));

    if (argc > 1)
        std::cerr << "Printing " << argv[1] << "\n";
    else
        std::cerr << "Printing with no input !\n";

    float camRadius = 15.0;
    for (int i = 0; i < nframes; i++)
    {
        std::cerr << "image : " << std::to_string(i) << "\n";
        float theta = i * 2 * glm::pi<float>() / nframes;
        renderer.camera.setPos(glm::vec3(camRadius * glm::sin(theta), 4.0, camRadius * glm::cos(theta)));

        renderer.render(scene);
        renderer.framebuffer.savePPM(("images\\image" + std::to_string(i) + ".ppm").c_str());
    }

    //-------------------------------------------------------------------------

    auto stop = std::chrono::high_resolution_clock::now();
    std::cerr << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0f << " s\n";
    return 0;
}