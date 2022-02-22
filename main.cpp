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
#include "src/Shapes.h"
#include "src/Data.h"

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

    int width = 1920;
    int height = 1080;

    DATA_camSpecs camSpecs = {
        {0.0f, 30.0f, -200.0f}, // Position
        {0.0f, 10.0f, -100.0f}, // Look at
        {0.0f, 1.0f, 0.0f},     // Up
        (float)width / height,  // Aspect Ratio
        40.0f                   // FOV
    };

    //-------------------------------------------------------------------------

    Scene scene;
    RayTracer renderer(camSpecs, width, height);
    int nframes = 1;

    scene.addMaterial(std::make_shared<Solid>(Solid({0.0f, 0.5f, 0.5f})));
    scene.addMaterial(std::make_shared<Solid>(Solid({0.1f, 0.2f, 0.9f})));
    scene.addMaterial(std::make_shared<Solid>(Solid({0.9f, 0.0f, 0.3f})));

    scene.addMaterial(std::make_shared<Solid>(Solid({0.5f, 0.5f, 0.5f})));

    // Old test Scene
    // for (int i = 0; i < 5; i++)
    //     scene.addShape(std::make_shared<Sphere>(Sphere({-4.0f + i * 2, 1.0f, 0.0f}, 1.0f, *scene.materials[0])));
    float sphereRadius = 15.0f;
    // for (int i = 0; i < 5; i++)
    //     scene.addShape(std::make_shared<Sphere>(Sphere({0.0f, 1.0f, -4.0f + i * 2}, 1.0f, *scene.materials[0])));

    scene.addShape(std::make_shared<Sphere>(Sphere({0.0f, -32.7f, 0.0f}, sphereRadius, *scene.materials[0])));
    scene.addShape(std::make_shared<Sphere>(Sphere({-5.98f, 0.0f, -22.31f}, sphereRadius, *scene.materials[1])));
    scene.addShape(std::make_shared<Sphere>(Sphere({-16.32f, 0.0f, 16.32f}, sphereRadius, *scene.materials[2])));
    scene.addShape(std::make_shared<Sphere>(Sphere({22.31f, 0.0f, 5.98f}, sphereRadius, *scene.materials[0])));
    scene.addShape(std::make_shared<Sphere>(Sphere({5.98f, -32.66f, 22.31f}, sphereRadius, *scene.materials[1])));
    scene.addShape(std::make_shared<Sphere>(Sphere({16.32f, -32.66f, -16.32f}, sphereRadius, *scene.materials[2])));
    scene.addShape(std::make_shared<Sphere>(Sphere({-22.31f, -32.66f, -5.98f}, sphereRadius, *scene.materials[0])));
    scene.addShape(std::make_shared<Sphere>(Sphere({-11.95f, -32.66f, -44.61f}, sphereRadius, *scene.materials[1])));
    scene.addShape(std::make_shared<Sphere>(Sphere({-32.66f, -32.66f, 32.66f}, sphereRadius, *scene.materials[2])));
    scene.addShape(std::make_shared<Sphere>(Sphere({44.61f, -32.66f, 11.95f}, sphereRadius, *scene.materials[0])));

    // SKY
    // scene.addShape(std::make_shared<Sphere>(Sphere({0.0f, -0.0f, 0.0f}, 600, *scene.materials[0])));

    // scene.addShape(std::make_shared<Sphere>(Sphere({0.0f, -1052.66f, 0.0f}, 1000.0f, *scene.materials[1])));

    if (argc > 1)
        std::cerr << "Printing " << argv[1] << "\n";
    else
        std::cerr << "Printing with no input !\n";

    float camRadius = 15.0;
    for (int i = 0; i < nframes; i++)
    {
        std::cerr << "Calculating image : " << std::to_string(i) << "\n";
        // float theta = i * 2 * glm::pi<float>() / nframes;
        //  renderer.camera.setPos(glm::vec3(camRadius * glm::sin(theta), 4.0, camRadius * glm::cos(theta)));

        renderer.render(scene, 30, 8); // samples, bounces

        std::cerr << "Printing image : " << std::to_string(i) << "\n";
        renderer.framebuffer.savePPM(("images\\image" + std::to_string(i) + ".ppm").c_str());
    }

    //-------------------------------------------------------------------------

    auto stop = std::chrono::high_resolution_clock::now();
    std::cerr << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0f << " s\n";
    return 0;
}