#include "aimbot.hpp"
#include <stdio.h>
#include <math.h>

// Enum pour les zones à viser
enum class Bone {
    HEAD,
    NECK,
    CHEST,
    PELVIS,
    L_HAND,
    R_HAND,
    L_FOOT,
    R_FOOT
};

// Paramètres de l'aimbot
struct AimbotSettings {
    bool enabled = false;
    Bone targetBone = Bone::HEAD;
    float fov = 90.0f;
    float smooth = 0.5f;
    bool checkVisible = false;
};

// Classe principale de l'aimbot
class Aimbot {
public:
    AimbotSettings settings;

    void Toggle() { settings.enabled = !settings.enabled; }
    void SetBone(Bone bone) { settings.targetBone = bone; }
    void SetFov(float f) { settings.fov = f; }
    void SetSmooth(float s) { settings.smooth = s; }
    void SetCheckVisible(bool v) { settings.checkVisible = v; }

    // Simulation d'une cible (à remplacer par l'intégration FiveM)
    struct Target {
        uintptr_t ped;
        float x, y, z;
        bool visible;
    };

    // Retourne la cible la plus proche dans le FOV
    Target* FindBestTarget(const std::vector<Target>& targets, float playerX, float playerY, float playerZ) {
        Target* best = nullptr;
        float bestDist = settings.fov;
        for (const auto& t : targets) {
            if (settings.checkVisible && !t.visible) continue;
            float dist = sqrtf(powf(t.x - playerX, 2) + powf(t.y - playerY, 2));
            if (dist < bestDist) {
                bestDist = dist;
                best = const_cast<Target*>(&t);
            }
        }
        return best;
    }

    // Applique le smooth à la visée (simulation)
    void AimAt(Target* target, float& aimX, float& aimY, float playerX, float playerY) {
        if (!target) return;
        float dx = target->x - playerX;
        float dy = target->y - playerY;
        aimX += dx * settings.smooth;
        aimY += dy * settings.smooth;
    }
};

// Menu console simple pour tester
void menu(Aimbot& aimbot) {
    while (1) {
        printf("\nAimbot Menu\n");
        printf("1. Toggle Aimbot (%s)\n", aimbot.settings.enabled ? "ON" : "OFF");
        printf("2. Select Bone (Current: ");
        switch (aimbot.settings.targetBone) {
            case Bone::HEAD:   printf("Head"); break;
            case Bone::NECK:   printf("Neck"); break;
            case Bone::CHEST:  printf("Chest"); break;
            case Bone::PELVIS: printf("Pelvis"); break;
            case Bone::L_HAND: printf("L-Hand"); break;
            case Bone::R_HAND: printf("R-Hand"); break;
            case Bone::L_FOOT: printf("L-Foot"); break;
            case Bone::R_FOOT: printf("R-Foot"); break;
            default:           printf("Unknown"); break;
        }
        printf(")\n");
        printf("3. Set FOV (%.2f)\n", aimbot.settings.fov);
        printf("4. Set Smooth (%.2f)\n", aimbot.settings.smooth);
        printf("5. Toggle Visibility Check (%s)\n", aimbot.settings.checkVisible ? "ON" : "OFF");
        printf("6. Exit\n");
        int input = 0;
        scanf("%d", &input);
        if (input < 1 || input > 6) continue;
        switch (input) {
            case 1:
                aimbot.Toggle();
                break;
            case 2: {
                printf("Select Bone:\n0.Head\n1.Neck\n2.Chest\n3.Pelvis\n4.L-Hand\n5.R-Hand\n6.L-Foot\n7.R-Foot\n");
                int b = 0; scanf("%d", &b);
                if (b >= 0 && b <= 7) aimbot.SetBone((Bone)b);
                break;
            }
            case 3: {
                printf("Enter FOV (float): ");
                float f = 0; scanf("%f", &f);
                if (f > 0) aimbot.SetFov(f);
                break;
            }
            case 4: {
                printf("Enter Smooth (0.0 - 1.0): ");
                float s = 0; scanf("%f", &s);
                if (s >= 0.0f && s <= 1.0f) aimbot.SetSmooth(s);
                break;
            }
            case 5:
                aimbot.SetCheckVisible(!aimbot.settings.checkVisible);
                break;
            case 6:
                return;
            default:
                break;
        }
    }
}

Aimbot g_aimbot; // Instance globale

void InitAimbot() {
    // Initialisation personnalisée si besoin
}

void RunAimbotMenu() {
    menu(g_aimbot);
}
