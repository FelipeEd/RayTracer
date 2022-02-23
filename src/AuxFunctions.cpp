#include "AuxFunctions.h"

inline int fastrand()
{
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

float random_float()
{
    return fastrand() / (RAND_MAX + 1.0f);
}

void printStatus()
{
    static int count = 0;
    std::cerr << "\r";
    for (int i = 0; i < 10; i++)
    {
        std::cerr << "\b";
    }

    std::string ready = "[";
    std::string notready = "";

    for (int i = 0; i < count; i++)
    {
        ready += "#";
    }
    for (int i = 0; i < 10 - count; i++)
    {
        notready += "-";
    }
    notready += "]";

    std::cerr << ready + notready;
    if (count == 10)
        std::cerr << "\n";
    count++;
}
