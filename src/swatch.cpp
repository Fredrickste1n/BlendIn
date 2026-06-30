#include <iostream>
#include <cmath>
#include <raylib.h>
#include "swatch.h"

Swatch::Swatch(float xPos, float yPos, float w, float h, float spd) {
    x = xPos;
    y = yPos;
    width = w;
    height = h;
    speed = spd;
    speedNorm = spd;
    speedTrig = sqrt(pow(spd, 2) / 2);
}

void Swatch::Draw() {
    std::cout << x << ", " << y << ", " << width << ", " << height << ", " << std::endl;
    DrawRectangle(x, y, width, height, Color{230, 226, 117, 255});
}

void Swatch::Update() {
    bool up = IsKeyDown(KEY_UP);
    bool down = IsKeyDown(KEY_DOWN);
    bool left = IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_RIGHT);

    // Sets speed to allow same speed at angle compared to vert/horiz
    if((up && (left || right)) || (down && (left || right))) {
        speed = speedTrig;
    } else {
        speed = speedNorm;
    }

    if(IsKeyDown(KEY_LEFT_SHIFT)) {
        speed /= 4;
    } else if(IsKeyDown(KEY_LEFT_CONTROL)) {
        speed *= 4;
    }

    if(up && y > 0) {
        y -= speed;
    }
    if(down && y + height < GetScreenHeight()) {
        y += speed;
    }
    if(left && x > 0) {
        x -= speed;
    }
    if(right && x + width < GetScreenWidth()) {
        x += speed;
    }
}