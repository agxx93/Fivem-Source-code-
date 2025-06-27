#pragma once
#include <string>

extern bool aimAssistEnabled, aimOnKey;
extern float aimSmoothing, aimFov;

extern bool infiniteAmmo, infiniteDamage;

extern bool boxEnabled, skeletonEnabled, distanceEnabled;
extern bool nameEnabled, weaponEnabled, healthEnabled;
extern float crosshairColor[3];
extern float menuColor[4];

extern bool vehicleGodmode, vehicleDemiGodmode, forceEngine;
extern bool repairVehicle, rocketBoost, parachute, jumping, ramming;

extern bool playerGodmode, playerDemiGodmode, regenerateArmor;
extern bool forceWantedLevel, noCollision;
extern float swimSpeed;

extern bool crosshairEnabled;

// Config
void LoadConfig(const std::string& file);
void SaveConfig(const std::string& file);
