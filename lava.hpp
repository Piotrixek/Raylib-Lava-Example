#ifndef LAVA_HPP
#define LAVA_HPP

#include "raylib.h"

class Lava {
public:
    
    Lava();
    ~Lava();

    
    void Load(const char* vsPath, const char* fsPath);

    void Update();
    void Draw();

private:
    Shader shader;
    Model model;
    int timeLoc;
    float runningTime;
    bool isLoaded; 
};

#endif 