#include <iostream>
#include <glm\glm.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <memory>

#include "src/RayTracer.h"
#include "src/Scene.h"
#include "src/Sphere.h"

int main(int argc, char **argv)
{
    auto start = std::chrono::high_resolution_clock::now();

    //-------------------------------------------------------------------------
    Scene scene;
    RayTracer renderer;

    scene.add(std::make_shared<Sphere>(Sphere({0.0f, 0.0f, -3.0f}, 1.0f)));
    scene.add(std::make_shared<Sphere>(Sphere({0.0f, 2.0f, -3.0f}, 1.0f)));
    scene.add(std::make_shared<Sphere>(Sphere({0.0f, -2.0f, -3.0f}, 1.0f)));

    if (argc > 1)
        std::cerr << "printing " << argv[1] << "\n";
    else
        std::cerr << "printing with no input\n";

    renderer.render(scene);

    if (argc > 2)
        renderer.framebuffer.savePPM(argv[2]);
    else
        renderer.framebuffer.savePPM("image.ppm");
    //-------------------------------------------------------------------------

    auto stop = std::chrono::high_resolution_clock::now();
    std::cerr << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0f << " s\n";
    return 0;
}