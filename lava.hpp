#ifndef LAVA_HPP
#define LAVA_HPP

#include "raylib.h"
#include "UIManager.hpp"

class Lava {
public:
    Lava();
    ~Lava();

    void Load();

    void Update(const UIManager& ui);
    void Draw();

private:
    Shader shader;
    Model model;
    bool isLoaded;
    float runningTime;

    int timeLoc;
    int speedLoc;
    int zoomLoc;
    int distortionLoc;
    int crustinessLoc;
    int pulseSpeedLoc;
    int hotColorLoc;
    int midColorLoc;
    int crustColorLoc;
};

#endif // LAVA_HPP