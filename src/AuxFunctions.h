#pragma once

#include <random>
#include <iostream>

static unsigned int g_seed;

// Generates a fast random integer
inline int fastrand();

// Generates a Fast random float in [,1)
float random_float();

// Prints a status bar
// must be called every 10% progress
void printStatus();
