#include "lava.hpp"
#include "rlgl.h"

Lava::Lava() : runningTime(0.0f), isLoaded(false) {
    shader = { 0 };
    model = { 0 };
    timeLoc = 0;
}

Lava::~Lava() {
    if (isLoaded) {
        UnloadShader(shader);
        UnloadModel(model);
    }
}


void Lava::Load(const char* vsPath, const char* fsPath) {
    shader = LoadShader(vsPath, fsPath);
    timeLoc = GetShaderLocation(shader, "time");

    Mesh plane = GenMeshPlane(10.0f, 10.0f, 50, 50);
    model = LoadModelFromMesh(plane);

    model.materials[0].shader = shader;
    isLoaded = true;
}

void Lava::Update() {
    if (isLoaded) {
        runningTime += GetFrameTime();
        SetShaderValue(shader, timeLoc, &runningTime, SHADER_UNIFORM_FLOAT);
    }
}

void Lava::Draw() {
    if (isLoaded) {
        DrawModel(model, { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
    }
}