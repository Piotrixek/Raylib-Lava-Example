#include "game.hpp"

Game::Game(int width, int height, const char* title)
    : screenWidth(width), screenHeight(height) {

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);

    lavaObject.Load("assets/lava.vs", "assets/lava.fs");

    camera = { 0 };
    camera.position = Vector3{ 5.0f, 5.0f, 5.0f };
    camera.target = Vector3{ 0.0f, 0.5f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

Game::~Game() {
    CloseWindow();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

void Game::Update() {
    UpdateCamera(&camera, CAMERA_ORBITAL);
    lavaObject.Update();
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(camera);
    {
        lavaObject.Draw();
        DrawGrid(20, 1.0f);
    }
    EndMode3D();

    DrawFPS(10, 10);
    DrawText("Move camera with mouse, scroll to zoom", 10, 40, 20, WHITE);

    EndDrawing();
}