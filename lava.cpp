#include "lava.hpp"
#include "rlgl.h"
#include <stdio.h>

const char* vertexShaderCode = R"(
#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

out vec2 fragTexCoord;

uniform mat4 mvp;

void main()
{
    fragTexCoord = vertexTexCoord;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
)";

const char* fragmentShaderCode = R"(
#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform float time;
uniform float speed;
uniform float zoom;
uniform float distortion;
uniform float crustiness;
uniform float pulseSpeed;
uniform vec3 hotColor;
uniform vec3 midColor;
uniform vec3 crustColor;

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.y * u.x;
}

float fbm(vec2 st) {
    float value = 0.0;
    float amplitude = 0.5;
    for (int i = 0; i < 6; i++) {
        value += amplitude * noise(st);
        st *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}

void main()
{
    vec2 st = fragTexCoord * zoom;
    float timeScaled = time * speed;
    vec2 q = vec2(fbm(st), fbm(st + vec2(5.2, 1.3))) * distortion;
    vec2 r = vec2(fbm(st + q + vec2(1.7, 9.2) + 0.15 * timeScaled), fbm(st + q + vec2(8.3, 2.8) + 0.126 * timeScaled)) * distortion;
    float f = fbm(st + r);
    float midPoint = crustiness * 0.5;
    float highPoint = crustiness;
    vec3 color = mix(crustColor, midColor, smoothstep(midPoint, highPoint, f));
    color = mix(color, hotColor, smoothstep(highPoint, highPoint + 0.2, f));
    float pulse = 0.7 + 0.3 * sin(timeScaled * pulseSpeed);
    finalColor = vec4(color * pulse, 1.0);
}
)";


Lava::Lava() : runningTime(0.0f), isLoaded(false) {
    shader = { 0 };
    model = { 0 };
    timeLoc = speedLoc = zoomLoc = distortionLoc = crustinessLoc = 0;
    pulseSpeedLoc = hotColorLoc = midColorLoc = crustColorLoc = 0;
}

Lava::~Lava() {
    if (isLoaded) {
        UnloadShader(shader);
        UnloadModel(model);
    }
}

void Lava::Load() {
    shader = LoadShaderFromMemory(vertexShaderCode, fragmentShaderCode);

    timeLoc = GetShaderLocation(shader, "time");
    speedLoc = GetShaderLocation(shader, "speed");
    zoomLoc = GetShaderLocation(shader, "zoom");
    distortionLoc = GetShaderLocation(shader, "distortion");
    crustinessLoc = GetShaderLocation(shader, "crustiness");
    pulseSpeedLoc = GetShaderLocation(shader, "pulseSpeed");
    hotColorLoc = GetShaderLocation(shader, "hotColor");
    midColorLoc = GetShaderLocation(shader, "midColor");
    crustColorLoc = GetShaderLocation(shader, "crustColor");

    printf("--- Shader Uniform Locations (From Memory) ---\n");
    printf("time: %d\n", timeLoc);
    printf("speed: %d\n", speedLoc);
    printf("zoom: %d\n", zoomLoc);
    printf("---------------------------------------------\n");

    Mesh plane = GenMeshPlane(10.0f, 10.0f, 50, 50);
    model = LoadModelFromMesh(plane);
    model.materials[0].shader = shader;
    isLoaded = true;
}

void Lava::Update(const UIManager& ui) {
    if (isLoaded) {
        runningTime += GetFrameTime();

        float speed = ui.GetSpeed();
        float zoom = ui.GetZoom();
        float distortion = ui.GetDistortion();
        float crustiness = ui.GetCrustiness();
        float pulseSpeed = ui.GetPulseSpeed();

        Vector3 hotColor = { ui.GetHotColor().r / 255.f, ui.GetHotColor().g / 255.f, ui.GetHotColor().b / 255.f };
        Vector3 midColor = { ui.GetMidColor().r / 255.f, ui.GetMidColor().g / 255.f, ui.GetMidColor().b / 255.f };
        Vector3 crustColor = { ui.GetCrustColor().r / 255.f, ui.GetCrustColor().g / 255.f, ui.GetCrustColor().b / 255.f };

        SetShaderValue(shader, timeLoc, &runningTime, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, speedLoc, &speed, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, distortionLoc, &distortion, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, crustinessLoc, &crustiness, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, pulseSpeedLoc, &pulseSpeed, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, hotColorLoc, &hotColor, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, midColorLoc, &midColor, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, crustColorLoc, &crustColor, SHADER_UNIFORM_VEC3);
    }
}

void Lava::Draw() {
    if (isLoaded) {
        DrawModel(model, { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
    }
}