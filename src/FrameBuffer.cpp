#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int w, int h)
{
    width = w;
    height = h;
    data.resize(height * width);

    for (int i = 0; i < width * height; i++)
    {
        data[i] = glm::vec3(0.0, 0.0, 0.0);
    }
}

void FrameBuffer::savePPM(const char *fileName)
{
    std::ofstream ofs(fileName, std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl
        << width << ' ' << height << std::endl
        << "255" << std::endl;

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            ofs << (char)(data[i + j * width].r * 255) << (char)(data[i + j * width].g * 255) << (char)(data[i + j * width].b * 255);

    ofs.close();
}

glm::vec3 &FrameBuffer::at(int i, int j)
{
    if (i > width || j > height)
    {
        std::cerr << "FrameBuffer Access out of Bounds\n";
        exit(0);
    }
    return data[i + j * width];
}
