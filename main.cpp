#include "game.hpp"

int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    Game game(screenWidth, screenHeight, "Raylib 3D Animated Lava");
    game.Run();

    return 0;
}