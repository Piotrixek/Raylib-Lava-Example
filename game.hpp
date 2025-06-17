#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "lava.hpp"
#include "UIManager.hpp"

class Game {
public:
    Game(int width, int height, const char* title);
    ~Game();

    void Run();

private:
    void Update();
    void Draw();

    int screenWidth;
    int screenHeight;
    Camera3D camera;
    Lava lavaObject;
    UIManager uiManager;
};

#endif // GAME_HPP