#include "vehicle.hpp"
#include "Offsets.hpp"
#include <Windows.h>
#include <cstdint>

namespace vehicle {
    bool godmode = false, semiGod = false, explode = false, repair = false;
    bool turbo = false, rocket = false, stealPlate = false, rain = false;
}

void InitVehicleMods() {}

void UpdateVehicleMods() {
    uintptr_t vehiclePtr = *reinterpret_cast<uintptr_t*>(Offsets::vehiclePtr);
    if (!vehiclePtr) return;

    if (vehicle::godmode) {
        // *(bool*)(vehiclePtr + Offsets::vehicleGodmode) = true;
    }
    if (vehicle::semiGod) {
        // *(float*)(vehiclePtr + Offsets::vehicleDamageReduction) = 0.5f;
    }
    if (vehicle::explode) {
        // *(bool*)(vehiclePtr + Offsets::explodeFlag) = true;
    }
    if (vehicle::repair) {
        // *(bool*)(vehiclePtr + Offsets::repairFlag) = true;
    }
    if (vehicle::turbo) {
        // *(bool*)(vehiclePtr + Offsets::turboFlag) = true;
    }
    if (vehicle::rocket) {
        // *(bool*)(vehiclePtr + Offsets::rocketFlag) = true;
    }
    if (vehicle::stealPlate) {
        // *(bool*)(vehiclePtr + Offsets::stealPlateFlag) = true;
    }
    if (vehicle::rain) {
        // *(bool*)(vehiclePtr + Offsets::rainFlag) = true;
    }
}
