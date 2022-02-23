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

    int width = 1280;
    int height = 720;
    int samples = 4;
    int bounces = 2;

    // TODO These must be read from a input file
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

    // Lights
    // scene.addLight(std::make_shared<Light>(Light({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.0f, 0.0f)));
    scene.addLight(std::make_shared<Light>(Light({60.0f, 160.0f, -200.0f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.0f, 0.0f)));
    // scene.addLight(std::make_shared<Light>(Light({-80.0f, 160.0f, -200.0f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.0f, 0.0f)));

    // Textures
    scene.addTexture(std::make_shared<Solid>(Solid({0.5f, 0.2f, 0.5f})));
    scene.addTexture(std::make_shared<Checker>(Checker({0.08f, 0.25f, 0.20f}, {0.93f, 0.83f, 0.82f}, 40.0f)));
    scene.addTexture(std::make_shared<Solid>(Solid({0.9f, 0.9f, 0.9f})));

    // Materials
    // ka kd ks alpha kr kt ior
    scene.addMaterial(std::make_shared<DATA_materialPhys>(DATA_materialPhys({0.80f, 0.00f, 0.00f, 1.0f, 0.0f, 0.0f, 0.0f})));
    scene.addMaterial(std::make_shared<DATA_materialPhys>(DATA_materialPhys({0.30f, 0.40f, 0.00f, 1.0f, 0.3f, 0.0f, 0.0f})));
    scene.addMaterial(std::make_shared<DATA_materialPhys>(DATA_materialPhys({0.11f, 0.11f, 0.30f, 1000.0f, 0.7f, 0.0f, 0.0f})));

    float sphereRadius = 20.0f;
    scene.addShape(std::make_shared<Sphere>(Sphere({0.0f, 32.7f, 0.0f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({-5.98f, 0.0f, -22.31f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({-16.32f, 0.0f, 16.32f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({22.31f, 0.0f, 5.98f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({5.98f, -32.66f, 22.31f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({16.32f, -32.66f, -16.32f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({-22.31f, -32.66f, -5.98f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({-11.95f, -32.66f, -44.61f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({-32.66f, -32.66f, 32.66f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));
    scene.addShape(std::make_shared<Sphere>(Sphere({44.61f, -32.66f, 11.95f},
                                                   sphereRadius,
                                                   *scene.getTexture(2),
                                                   *scene.getMaterial(2))));

    // SKY
    scene.addShape(std::make_shared<Sphere>(Sphere({0.0f, -0.0f, 0.0f}, 600,
                                                   *scene.getTexture(0),
                                                   *scene.getMaterial(0))));

    scene.addShape(std::make_shared<Sphere>(Sphere({0.0f, -1052.66f, 0.0f}, 1000.0f,
                                                   *scene.getTexture(1),
                                                   *scene.getMaterial(1))));

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

        renderer.render(scene, samples, bounces); // samples, bounces

        std::cerr << "Printing image : " << std::to_string(i) << "\n";
        renderer.framebuffer.savePPM(("images\\image" + std::to_string(i) + ".ppm").c_str());
    }

    //-------------------------------------------------------------------------

    auto stop = std::chrono::high_resolution_clock::now();
    std::cerr << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0f << " s\n";
    return 0;
}