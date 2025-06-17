#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include "raylib.h"

class UIManager {
public:
    UIManager();

    void Setup();
    void Shutdown();
    void Begin();
    void End();

    void DrawControls();

    float GetSpeed() const;
    float GetZoom() const;
    float GetDistortion() const;
    float GetCrustiness() const;
    float GetPulseSpeed() const;
    Color GetHotColor() const;
    Color GetMidColor() const;
    Color GetCrustColor() const;

private:

    float speed;
    float zoom;
    float distortion;
    float crustiness;
    float pulseSpeed;
    Color hotColor;
    Color midColor;
    Color crustColor;
};

#endif // UIMANAGER_HPP