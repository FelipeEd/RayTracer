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

// Print vec 3
void pv3(const char *frase, glm::vec3 a)
{
    std::cerr << frase
              << "  ";
    std::cerr << a.x << " " << a.y << " " << a.z << "\n";
}

struct App
{
    Scene scene;
    RayTracer raytracer;
};

App readInputFile(const char *filename, int w, int h);

int main(int argc, char **argv)
{
    // Configs-----------------------------------------------
    int samples = 30;
    int bounces = 10;
    bool imperfectShadows = true;
    bool imperfectReflections = false;
    //-------------------------------------------------------

    auto start = std::chrono::high_resolution_clock::now();
    App app;
    if (argc == 5)
        app = readInputFile(argv[1], std::stoi(argv[3]), std::stoi(argv[4]));
    else
        app = readInputFile(argv[1], 800, 600);

    Scene scene = app.scene;
    RayTracer renderer = app.raytracer;

    renderer.imperfectReflection = imperfectReflections;
    renderer.imperfectShadows = imperfectShadows;

    if (argc > 1)
        std::cerr << "Printing " << argv[1] << "\n";
    else
        std::cerr << "Printing with no input !\n";

    std::cerr << "Calculating image :\n";
    renderer.render(scene, samples, bounces); // samples, bounces

    std::cerr << "Printing image :\n";
    std::string imageName = argv[2];
    std::string filePath = "images\\" + imageName;

    renderer.framebuffer.savePPM(filePath.c_str());

    //-------------------------------------------------------------------------

    auto stop = std::chrono::high_resolution_clock::now();
    std::cerr << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000000.0f << " s\n";

    return 0;
}

App readInputFile(const char *filename, int w, int h)
{
    using namespace std;
    ifstream ifs(filename);
    Scene scene;

    DATA_camSpecs camSpecs;

    camSpecs.aspectRatio = (float)w / h;
    // Load camera
    ifs >> camSpecs.position.x >> camSpecs.position.y >> camSpecs.position.z;
    ifs >> camSpecs.lookat.x >> camSpecs.lookat.y >> camSpecs.lookat.z;
    ifs >> camSpecs.up.x >> camSpecs.up.y >> camSpecs.up.z;
    ifs >> camSpecs.FOV;

    RayTracer raytracer(camSpecs, w, h);

    // load lights
    int nLights = 0;
    ifs >> nLights;

    for (int i = 0; i < nLights; i++)
    {
        glm::vec3 pos, color;
        float c, l, s;
        ifs >> pos.x >> pos.y >> pos.z >> color.x >> color.y >> color.z >> c >> l >> s;
        scene.addLight(make_shared<Light>(Light(pos, color, c, l, s)));
    }

    // Load pigments
    int nPigments = 0;
    ifs >> nPigments;

    for (int i = 0; i < nPigments; i++)
    {
        glm::vec3 color1, color2;
        glm::vec4 p0, p1;
        float cubesize;
        string type, texturename;

        ifs >> type;
        if (type == "solid")
        {
            ifs >> color1.x >> color1.y >> color1.z;
            scene.addTexture(make_shared<Solid>(Solid(color1)));
        }
        if (type == "checker")
        {
            ifs >> color1.x >> color1.y >> color1.z >> color2.x >> color2.y >> color2.z >> cubesize;
            scene.addTexture(make_shared<Checker>(Checker(color1, color2, cubesize)));
        }
        if (type == "texmap")
        {
            ifs >> texturename;
            ifs >> p0.x >> p0.y >> p0.z >> p0.w;
            ifs >> p1.x >> p1.y >> p1.z >> p1.w;
            scene.addTexture(make_shared<Solid>(Solid({0.0f, 0.5f, 0.5f})));
        }
    }

    // Loading Materials
    int nMaterials = 0;
    ifs >> nMaterials;

    for (int i = 0; i < nMaterials; i++)
    {
        float ka, kd, ks, alpha, kr, kt, ior;
        ifs >> ka >> kd >> ks >> alpha >> kr >> kt >> ior;
        scene.addMaterial(make_shared<DATA_materialPhys>(DATA_materialPhys{ka, kd, ks, alpha, kr, kt, ior}));
    }

    // Loading Shapes
    int nShapes = 0;
    ifs >> nShapes;

    for (int i = 0; i < nShapes; i++)
    {
        int tex, mat, nPlanes;
        glm::vec3 pos;
        float radius;
        string type;
        ifs >> tex >> mat >> type;
        if (type == "sphere")
        {
            ifs >> pos.x >> pos.y >> pos.z >> radius;

            scene.addShape(std::make_shared<Sphere>(Sphere(pos,
                                                           radius,
                                                           *scene.getTexture(tex),
                                                           *scene.getMaterial(mat))));
        }

        if (type == "polyhedron")
        {
            vector<glm::vec4> faces;
            float a, b, c, d;

            ifs >> nPlanes;
            for (int j = 0; j < nPlanes; j++)
            {
                ifs >> a >> b >> c >> d;
                faces.push_back({a, b, c, d});
            }
            scene.addShape(std::make_shared<Polyhedron>(Polyhedron(faces,
                                                                   *scene.getTexture(tex),
                                                                   *scene.getMaterial(mat))));
        }
    }

    ifs.close();
    return App{scene, raytracer};
}