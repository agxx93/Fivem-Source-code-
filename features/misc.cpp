#include "misc.hpp"
#include "Offsets.hpp"
#include <Windows.h>
#include <cstdint>

namespace misc {
    bool crosshair = false;
    float crosshairColor[3] = {1.f, 1.f, 1.f};
    float menuColor[3] = {0.2f, 0.5f, 1.f};
    bool freecam = false;
    float noclipSpeed = 10.f;
    float altitude = 20.f;
    int hp = 200, armor = 100, time = 12, weather = 0;
    bool autoHeal = false;
}

void InitMisc() {}

void UpdateMisc() {
    uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>(Offsets::localPlayer);
    if (!localPlayer) return;

    if (misc::autoHeal) {
        // *(int*)(localPlayer + Offsets::health) = misc::hp;
    }
    // *(int*)(localPlayer + Offsets::armor) = misc::armor;
    // *(int*)(Offsets::timeOfDay) = misc::time;
    // *(int*)(Offsets::weatherType) = misc::weather;
    // ...autres options misc à appliquer via offsets...
}
