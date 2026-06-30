#include <iostream>
#include <raylib.h>

#pragma once

class Swatch {
public:
    float x, y, width, height, speed, speedTrig, speedNorm;

    Swatch(float, float, float, float, float);
    void Draw();
    void Update();
};