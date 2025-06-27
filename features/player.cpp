#include "player.hpp"
#include "Offsets.hpp"
#include <Windows.h>
#include <cstdint>

namespace player {
    bool trueGodmode = false, semiGod = false, noRagdoll = false, noCollision = false;
    bool noclip = false, rollbackBypass = false, stamina = false, onePunch = false, ghost = false;
    float swimSpeed = 1.0f, jumpBoost = 1.0f;
}

void InitPlayerMods() {}

void UpdatePlayerMods() {
    uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>(Offsets::localPlayer);
    if (!localPlayer) return;

    if (player::trueGodmode) {
        // *(bool*)(localPlayer + Offsets::godmode) = true;
    }
    if (player::semiGod) {
        // *(float*)(localPlayer + Offsets::damageReduction) = 0.5f;
    }
    if (player::noRagdoll) {
        // *(bool*)(localPlayer + Offsets::noRagdoll) = true;
    }
    if (player::noCollision) {
        // *(bool*)(localPlayer + Offsets::noCollision) = true;
    }
    if (player::noclip) {
        // *(bool*)(localPlayer + Offsets::noclip) = true;
    }
    if (player::rollbackBypass) {
        // ...rollback bypass logic...
    }
    if (player::stamina) {
        // *(float*)(localPlayer + Offsets::stamina) = 100.f;
    }
    if (player::onePunch) {
        // *(float*)(localPlayer + Offsets::meleeDamage) = 9999.f;
    }
    if (player::ghost) {
        // *(bool*)(localPlayer + Offsets::ghost) = true;
    }
    // swimSpeed, jumpBoost, etc. à appliquer via offsets
}
