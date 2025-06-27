#include "silent_aim.hpp"
#include "Offsets.hpp"
#include <Windows.h>
#include <cstdint>
#include <random>

namespace silentaim {
    bool enabled = false;
    float hitChance = 100.f;
    float fov = 60.f;
    bool magic = false;
}

namespace fivem {
    template<typename T>
    T Read(uintptr_t addr) {
        return *reinterpret_cast<T*>(addr);
    }
    template<typename T>
    void Write(uintptr_t addr, T value) {
        *reinterpret_cast<T*>(addr) = value;
    }
}

void InitSilentAim() {
    // ...init si besoin...
}

void RunSilentAim() {
    if (!silentaim::enabled) return;

    // Lire le joueur local et la liste d'entités via offsets
    uintptr_t localPlayer = fivem::Read<uintptr_t>(Offsets::localPlayer);
    uintptr_t entityList  = fivem::Read<uintptr_t>(Offsets::entityList);
    if (!localPlayer || !entityList) return;

    // Parcourir les entités pour trouver la meilleure cible dans le FOV
    uintptr_t bestTarget = 0;
    float bestFov = silentaim::fov;
    // ...loop sur entityList, calculer l'angle, choisir la cible la plus proche du crosshair...

    // Calculer la chance de hit
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 100);
    if (dis(gen) > silentaim::hitChance) return;

    // Appliquer la logique silent aim (changer la direction du tir sans bouger la caméra)
    if (bestTarget) {
        // Ex : modifier la direction du tir dans la mémoire du jeu
        // fivem::Write<Vec3>(Offsets::aimDirection, targetDirection);

        if (silentaim::magic) {
            // Magic bullet : forcer la balle à toucher la cible
            // fivem::Write<uintptr_t>(Offsets::bulletTarget, bestTarget);
        }
    }
}
