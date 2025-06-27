#include "visuals.hpp"
#include "Offsets.hpp"
#include <Windows.h>
#include <cstdint>

namespace visuals {
    bool enabled = true;
    bool box = false;
    bool wireframe = false;
    bool chams = false;
    bool skeleton = false;
    float skeletonThickness = 2.0f;
    bool names = false;
    bool weapon = false;
    bool health = false;
    bool armor = false;
    bool distance = false;
    bool snapline = false;
    bool cameraDir = false;
    bool radar = false;
    float radarZoom = 5.0f;
    bool arrow = false;
}

void InitESP() {}

void DrawESP() {
    if (!visuals::enabled) return;

    // Exemple d'utilisation des offsets pour lire la liste d'entités
    uintptr_t entityList = *reinterpret_cast<uintptr_t*>(Offsets::entityList);
    int entityCount = *reinterpret_cast<int*>(Offsets::entityCount);

    for (int i = 0; i < entityCount; ++i) {
        uintptr_t entity = *reinterpret_cast<uintptr_t*>(entityList + i * sizeof(uintptr_t));
        if (!entity) continue;

        // Ici, tu peux lire les infos de l'entité (position, vie, etc.) via offsets
        // et dessiner selon les options visuals::box, visuals::names, etc.

        // Exemple (pseudo-code) :
        // Vec3 pos = *reinterpret_cast<Vec3*>(entity + Offsets::entityPos);
        // if (visuals::box) DrawBox(pos, ...);
        // if (visuals::names) DrawName(pos, ...);
        // etc.
    }

    // Radar, snaplines, etc. à ajouter ici selon les flags visuals
}
