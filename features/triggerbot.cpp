#include "triggerbot.hpp"
#include "Offsets.hpp"
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cstdint>

namespace triggerbot {
    bool enabled = false;
    int delay = 0;
}

namespace fivem {
    template<typename T>
    T Read(uintptr_t addr) {
        return *reinterpret_cast<T*>(addr);
    }
}

void InitTriggerbot() {}

void RunTriggerbot() {
    if (!triggerbot::enabled)
        return;

    // Lire le pointeur du joueur local via l'offset
    uintptr_t localPlayer = fivem::Read<uintptr_t>(Offsets::localPlayer);
    if (!localPlayer) return;

    // Lire l'arme actuelle (exemple)
    uintptr_t weaponManager = fivem::Read<uintptr_t>(Offsets::weaponManager);
    // ...autres lectures mémoire selon besoin...

    // Logique de trigger : si une cible est sous le crosshair, tirer
    // (exemple simplifié, à adapter selon ton jeu)
    bool targetInCrosshair = false;
    // ...détection de la cible...

    if (targetInCrosshair) {
        std::this_thread::sleep_for(std::chrono::milliseconds(triggerbot::delay));
        // Simuler un tir (exemple interne)
        // *(bool*)(Offsets::shootFlag) = true;
    }
}
