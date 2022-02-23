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

glm::vec3 gammaCorrect(glm::vec3 color)
{
    float exp = 1 / (2.2f * 2);
    return glm::vec3(glm::pow(color.r, exp), glm::pow(color.g, exp), glm::pow(color.b, exp));
}

void FrameBuffer::savePPM(const char *fileName)
{
    bool NotNormalized = false;
    std::ofstream ofs(fileName, std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl
        << width << ' ' << height << std::endl
        << "255" << std::endl;

    for (int j = height - 1; j >= 0; j--)
        for (int i = 0; i < width; i++)
        {
            glm::vec3 pixColor = data[i + j * width];

            // pixColor = gammaCorrect(pixColor); //! GAMMA CORRECTION OFF

            if (pixColor.r > 1.f || pixColor.g > 1.f || pixColor.b > 1.f)
                NotNormalized = true;

            pixColor.r = glm::clamp(pixColor.r, 0.0f, 1.0f);
            pixColor.g = glm::clamp(pixColor.g, 0.0f, 1.0f);
            pixColor.b = glm::clamp(pixColor.b, 0.0f, 1.0f);

            ofs << (char)(pixColor.r * 255) << (char)(pixColor.g * 255) << (char)(pixColor.b * 255);
        }
    if (NotNormalized)
        std::cerr << "WARNING :: Pixel not normalized!\n";
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
