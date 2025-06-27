#include "weapons.hpp"
#include "Offsets.hpp"
#include <Windows.h>
#include <cstdint>
#include <vector>
#include <string>

namespace weapons {
    bool noRecoil = false, noSpread = false, explosive = false, infiniteAmmo = false;
    float damageMult = 1.0f, rangeMult = 100.0f;
}

// Liste d'IDs d'armes FiveM (exemple, à compléter selon le serveur)
enum WeaponHash : uint32_t {
    WEAPON_PISTOL = 0x1B06D571,
    WEAPON_COMBATPISTOL = 0x5EF9FEC4,
    WEAPON_APPISTOL = 0x22D8FE39,
    WEAPON_MICROSMG = 0x13532244,
    WEAPON_SMG = 0x2BE6766B,
    WEAPON_ASSAULTRIFLE = 0xBFEFFF6D,
    WEAPON_CARBINERIFLE = 0x83BF0278,
    WEAPON_ADVANCEDRIFLE = 0xAF113F99,
    WEAPON_MG = 0x9D07F764,
    WEAPON_COMBATMG = 0x7FD62962,
    WEAPON_PUMPSHOTGUN = 0x1D073A89,
    WEAPON_SAWNOFFSHOTGUN = 0x7846A318,
    WEAPON_ASSAULTSHOTGUN = 0xE284C527,
    WEAPON_BULLPUPSHOTGUN = 0x9D61E50F,
    WEAPON_SNIPERRIFLE = 0x05FC3C11,
    WEAPON_HEAVYSNIPER = 0x0C472FE2,
    WEAPON_GRENADELAUNCHER = 0xA284510B,
    WEAPON_RPG = 0xB1CA77B1,
    WEAPON_MINIGUN = 0x42BF8A85,
    // ...ajoute d'autres armes ici...
};

// Fonction pour donner une arme (bypass FiveGuard/WiseShield/GLife RP)
// L'arme est directement équipée dans la main et spoofée côté mémoire
void GiveWeaponBypass(uintptr_t playerPed, WeaponHash weapon, int ammo = 250) {
    uintptr_t weaponManager = *reinterpret_cast<uintptr_t*>(playerPed + OFFSET_WEAPON_MANAGER);
    if (!weaponManager) return;

    // Place l'arme dans la main (slot actif) et non dans l'inventaire
    uintptr_t currentWeaponSlot = weaponManager + OFFSET_CURRENT_WEAPON;
    uintptr_t weaponData = *reinterpret_cast<uintptr_t*>(currentWeaponSlot);

    // Sauvegarde l'ancien hash pour le restore si besoin
    uint32_t oldHash = *reinterpret_cast<uint32_t*>(weaponData + OFFSET_WEAPON_HASH);

    // Spoof : change le hash de l'arme active
    *reinterpret_cast<uint32_t*>(weaponData + OFFSET_WEAPON_HASH) = (uint32_t)weapon;
    *reinterpret_cast<int*>(weaponData + OFFSET_INFINITE_AMMO) = ammo;

    // Force l'équipement immédiat (dans la main)
    // *(bool*)(weaponData + OFFSET_EQUIP_NOW) = true; // À définir si tu as l'offset

    // Optionnel : restore l'ancien hash après un court délai pour spoof
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // *reinterpret_cast<uint32_t*>(weaponData + OFFSET_WEAPON_HASH) = oldHash;
}

void InitWeaponMods() {}

void UpdateWeaponMods() {
    uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>(OFFSET_LOCAL_PLAYER);
    if (!localPlayer) return;

    if (weapons::noRecoil) {
        // *(float*)(localPlayer + OFFSET_NO_RECOIL) = 0.f; // À définir si tu as l'offset
    }
    if (weapons::noSpread) {
        // *(float*)(localPlayer + OFFSET_NO_SPREAD) = 0.f; // À définir si tu as l'offset
    }
    if (weapons::explosive) {
        // *(bool*)(localPlayer + OFFSET_EXPLOSIVE_AMMO) = true; // À définir si tu as l'offset
    }
    if (weapons::infiniteAmmo) {
        uintptr_t weaponManager = *reinterpret_cast<uintptr_t*>(localPlayer + OFFSET_WEAPON_MANAGER);
        if (weaponManager) {
            uintptr_t currentWeaponSlot = weaponManager + OFFSET_CURRENT_WEAPON;
            uintptr_t weaponData = *reinterpret_cast<uintptr_t*>(currentWeaponSlot);
            *reinterpret_cast<int*>(weaponData + OFFSET_INFINITE_AMMO) = 9999;
        }
    }
    // Multiplier les dégâts et la portée
    // *(float*)(localPlayer + OFFSET_DAMAGE_MULTIPLIER) = weapons::damageMult;
    // *(float*)(localPlayer + OFFSET_RANGE_MULTIPLIER) = weapons::rangeMult; // À définir si tu as l'offset

    // Exemple : donner toutes les armes principales (bypass anti-cheat)
    std::vector<WeaponHash> allWeapons = {
        WEAPON_PISTOL, WEAPON_COMBATPISTOL, WEAPON_APPISTOL, WEAPON_MICROSMG,
        WEAPON_SMG, WEAPON_ASSAULTRIFLE, WEAPON_CARBINERIFLE, WEAPON_ADVANCEDRIFLE,
        WEAPON_MG, WEAPON_COMBATMG, WEAPON_PUMPSHOTGUN, WEAPON_SAWNOFFSHOTGUN,
        WEAPON_ASSAULTSHOTGUN, WEAPON_BULLPUPSHOTGUN, WEAPON_SNIPERRIFLE,
        WEAPON_HEAVYSNIPER, WEAPON_GRENADELAUNCHER, WEAPON_RPG, WEAPON_MINIGUN
        // ...complète la liste...
    };

    for (auto weapon : allWeapons) {
        GiveWeaponBypass(localPlayer, weapon, 999);
    }
}
