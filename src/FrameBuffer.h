#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <glm\glm.hpp>

class FrameBuffer
{
public:
    unsigned int width, height;  // Image dimensions
    std::vector<glm::vec3> data; // Pixel data

    FrameBuffer(int w, int h);
    ~FrameBuffer(){};

    void savePPM(const char *fileName);
    glm::vec3 &at(int i, int j);

private:
};

#endif