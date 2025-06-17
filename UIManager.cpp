#include "UIManager.hpp"
#include "rlImGui.h"
#include "imgui.h"

UIManager::UIManager() {
    speed = 1.0f;
    zoom = 3.0f;
    distortion = 1.0f;
    crustiness = 0.6f;
    pulseSpeed = 2.0f;
    hotColor = { 255, 255, 150, 255 };
    midColor = { 255, 80, 0, 255 };
    crustColor = { 30, 0, 0, 255 };
}

void UIManager::Setup() {
    rlImGuiSetup(true);
}

void UIManager::Shutdown() {
    rlImGuiShutdown();
}

void UIManager::Begin() {
    rlImGuiBegin();
}

void UIManager::End() {
    rlImGuiEnd();
}

void UIManager::DrawControls() {
    ImGui::Begin("Lava Controls");

    ImGui::Text("Movement & Pattern");
    ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
    ImGui::SliderFloat("Zoom", &zoom, 0.1f, 10.0f);
    ImGui::SliderFloat("Distortion", &distortion, 0.0f, 5.0f);
    ImGui::SliderFloat("Crustiness", &crustiness, 0.1f, 1.0f);

    ImGui::Separator();

    ImGui::Text("Color Gradient");
    float hot[3] = { hotColor.r / 255.0f, hotColor.g / 255.0f, hotColor.b / 255.0f };
    float mid[3] = { midColor.r / 255.0f, midColor.g / 255.0f, midColor.b / 255.0f };
    float crust[3] = { crustColor.r / 255.0f, crustColor.g / 255.0f, crustColor.b / 255.0f };

    if (ImGui::ColorEdit3("Hot Color", hot)) {
        hotColor = { (unsigned char)(hot[0] * 255), (unsigned char)(hot[1] * 255), (unsigned char)(hot[2] * 255), 255 };
    }
    if (ImGui::ColorEdit3("Mid Color", mid)) {
        midColor = { (unsigned char)(mid[0] * 255), (unsigned char)(mid[1] * 255), (unsigned char)(mid[2] * 255), 255 };
    }
    if (ImGui::ColorEdit3("Crust Color", crust)) {
        crustColor = { (unsigned char)(crust[0] * 255), (unsigned char)(crust[1] * 255), (unsigned char)(crust[2] * 255), 255 };
    }

    ImGui::Separator();
    ImGui::Text("Glow");
    ImGui::SliderFloat("Pulse Speed", &pulseSpeed, 0.0f, 10.0f);


    ImGui::End();
}


float UIManager::GetSpeed() const { return speed; }
float UIManager::GetZoom() const { return zoom; }
float UIManager::GetDistortion() const { return distortion; }
float UIManager::GetCrustiness() const { return crustiness; }
float UIManager::GetPulseSpeed() const { return pulseSpeed; }
Color UIManager::GetHotColor() const { return hotColor; }
Color UIManager::GetMidColor() const { return midColor; }
Color UIManager::GetCrustColor() const { return crustColor; }