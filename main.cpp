#include "imgui.h"
#include "aimbot.hpp"
#include "silent_aim.hpp"
#include "triggerbot.hpp"
#include "visuals.hpp"
#include "online.hpp"
#include "player.hpp"
#include "vehicle.hpp"
#include "weapons.hpp"
#include "misc.hpp"
#include "eventmanager.hpp"
#include "menu.hpp"

void RenderMenu() {
    ImGui::Begin("Freerot Trainer", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::BeginTabBar("MainTabs")) {

        if (ImGui::BeginTabItem("Aimbot")) {
            ImGui::Checkbox("Enable Aimbot", &aimbotEnabled);
            ImGui::SliderFloat("FOV", &aimbotFOV, 0.f, 180.f);
            ImGui::SliderFloat("Smoothing", &aimbotSmooth, 0.f, 1.f);
            ImGui::Checkbox("On Key", &aimbotOnKey);
            ImGui::Combo("Aimbot Target", &aimbot.targetMode, "Closest\0Head\0Body\0Random\0");
            ImGui::SliderInt("Aimbot Priority", &aimbot.priority, 0, 10);
            ImGui::Checkbox("Draw FOV Circle", &aimbot.drawFov);
            ImGui::ColorEdit4("FOV Circle Color", aimbot.fovColor);
            ImGui::Checkbox("Ignore Team", &aimbot.ignoreTeam);
            ImGui::Checkbox("Ignore Friends", &aimbot.ignoreFriends);
            ImGui::Checkbox("Auto Fire", &aimbot.autoFire);

            ImGui::SeparatorText("Triggerbot");
            ImGui::Checkbox("Enable Triggerbot", &triggerbot.enabled);
            ImGui::SliderInt("Trigger Delay", &triggerbot.delay, 0, 1000);
            ImGui::Checkbox("Triggerbot On Key", &triggerbot.onKey);
            ImGui::Combo("Triggerbot Mode", &triggerbot.mode, "Single\0Burst\0Auto\0");

            ImGui::SeparatorText("Silent Aim");
            ImGui::Checkbox("Enable Silent Aim", &silentaim.enabled);
            ImGui::SliderFloat("Hit Chance", &silentaim.hitChance, 0.f, 100.f);
            ImGui::SliderFloat("FOV", &silentaim.fov, 0.f, 180.f);
            ImGui::Checkbox("Magic Bullet", &silentaim.magic);
            ImGui::Checkbox("Silent Aim on Key", &silentaim.onKey);
            ImGui::Combo("Silent Aim Bone", &silentaim.bone, "Head\0Neck\0Chest\0Pelvis\0");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Visuals")) {
            ImGui::Checkbox("Enable Visuals", &visuals.enabled);
            ImGui::Checkbox("Box", &visuals.box);
            ImGui::Checkbox("Wireframe", &visuals.wireframe);
            ImGui::Checkbox("Chams", &visuals.chams);
            ImGui::Checkbox("Skeleton", &visuals.skeleton);
            ImGui::SliderFloat("Skeleton Thickness", &visuals.skeletonThickness, 1.f, 5.f);
            ImGui::Checkbox("Player Names", &visuals.names);
            ImGui::Checkbox("Weapon ESP", &visuals.weapon);
            ImGui::Checkbox("Health Bar", &visuals.health);
            ImGui::Checkbox("Armor Bar", &visuals.armor);
            ImGui::Checkbox("Distance", &visuals.distance);
            ImGui::Checkbox("Snaplines", &visuals.snapline);
            ImGui::Checkbox("Camera Indicator", &visuals.cameraDir);
            ImGui::Checkbox("Show Head Dot", &visuals.headDot);
            ImGui::ColorEdit4("Box Color", visuals.boxColor);
            ImGui::ColorEdit4("Chams Color", visuals.chamsColor);
            ImGui::SliderFloat("ESP Opacity", &visuals.espAlpha, 0.1f, 1.f);

            ImGui::SeparatorText("Radar");
            ImGui::Checkbox("Enable Radar", &visuals.radar);
            ImGui::SliderFloat("Radar Zoom", &visuals.radarZoom, 1.f, 10.f);
            ImGui::Checkbox("Arrow Direction", &visuals.arrow);
            ImGui::SliderInt("Radar Size", &visuals.radarSize, 50, 500);
            ImGui::ColorEdit4("Radar Color", visuals.radarColor);

            ImGui::SeparatorText("Advanced");
            ImGui::Checkbox("Show Vehicles", &visuals.vehicles);
            ImGui::Checkbox("Show Pickups", &visuals.pickups);
            ImGui::Checkbox("Show NPCs", &visuals.npcs);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Online")) {
            ImGui::Checkbox("Force All Players", &online.forceAll);
            ImGui::Checkbox("Kill All Players", &online.killAll);
            ImGui::Checkbox("Punch All Players", &online.punchAll);
            ImGui::Checkbox("Crash Players", &online.crashAll);
            ImGui::Checkbox("Bug All Vehicles", &online.bugVehicles);
            ImGui::SeparatorText("Player Interaction");
            ImGui::Checkbox("Teleport to Player", &online.teleportTo);
            ImGui::Checkbox("Add Friend", &online.addFriend);
            ImGui::Checkbox("Give Heal", &online.giveHeal);
            ImGui::Checkbox("Give Armor", &online.giveArmor);
            ImGui::Checkbox("Give Pistol", &online.givePistol);
            ImGui::Checkbox("Warp to Car", &online.warpCar);
            ImGui::Checkbox("Clone Ped", &online.clonePed);
            ImGui::Checkbox("Aggressive Clone", &online.cloneAggressive);
            ImGui::Checkbox("Cage Player", &online.cagePlayer);
            ImGui::Checkbox("Attach Car to Player", &online.attachCar);
            ImGui::Checkbox("Explode Player", &online.explode);
            ImGui::SeparatorText("Advanced");
            ImGui::Checkbox("Freeze All Players", &online.freezeAll);
            ImGui::Checkbox("Mute All Players", &online.muteAll);
            ImGui::Checkbox("Send Message to All", &online.sendMsgAll);
            ImGui::InputText("Message", online.message, IM_ARRAYSIZE(online.message));
            if (ImGui::Button("Send Message")) { online.sendMsgNow = true; }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Player")) {
            ImGui::Checkbox("True Godmode", &player.trueGodmode);
            ImGui::Checkbox("Demi Godmode", &player.semiGod);
            ImGui::Checkbox("No Ragdoll", &player.noRagdoll);
            ImGui::Checkbox("No Collision", &player.noCollision);
            ImGui::Checkbox("No Clip", &player.noclip);
            ImGui::Checkbox("Bypass Rollback", &player.rollbackBypass);
            ImGui::Checkbox("Infinite Stamina", &player.stamina);
            ImGui::SliderFloat("Swim Speed", &player.swimSpeed, 1.f, 10.f);
            ImGui::SliderFloat("Jump Height", &player.jumpBoost, 1.f, 20.f);
            ImGui::Checkbox("Super Punch", &player.onePunch);
            ImGui::Checkbox("Ghost Mode", &player.ghost);
            ImGui::SliderFloat("Run Speed", &player.runSpeed, 1.f, 10.f);
            ImGui::SliderFloat("Gravity", &player.gravity, 0.1f, 2.f);
            ImGui::Checkbox("Invisible", &player.invisible);
            ImGui::Checkbox("Never Wanted", &player.neverWanted);
            ImGui::SliderInt("Wanted Level", &player.wantedLevel, 0, 5);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Vehicle")) {
            ImGui::Checkbox("Vehicle Godmode", &vehicle.godmode);
            ImGui::Checkbox("Demi Vehicle Godmode", &vehicle.semiGod);
            ImGui::Checkbox("Explode Vehicle", &vehicle.explode);
            ImGui::Checkbox("Repair Vehicle", &vehicle.repair);
            ImGui::Checkbox("Enable Turbo", &vehicle.turbo);
            ImGui::Checkbox("Rocket Boost", &vehicle.rocket);
            ImGui::Checkbox("Steal Plate", &vehicle.stealPlate);
            ImGui::Checkbox("Vehicle Rain (Blackhole)", &vehicle.rain);
            ImGui::SliderFloat("Vehicle Speed Multiplier", &vehicle.speedMult, 1.f, 10.f);
            ImGui::SliderFloat("Vehicle Gravity", &vehicle.gravity, 0.1f, 2.f);
            ImGui::Checkbox("Fly Mode", &vehicle.flyMode);
            ImGui::Checkbox("No Collision", &vehicle.noCollision);
            ImGui::Checkbox("Rainbow Paint", &vehicle.rainbowPaint);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Weapons")) {
            ImGui::Checkbox("No Recoil", &weapons.noRecoil);
            ImGui::Checkbox("No Spread", &weapons.noSpread);
            ImGui::Checkbox("Explosive Ammo", &weapons.explosive);
            ImGui::Checkbox("Infinite Ammo", &weapons.infiniteAmmo);
            ImGui::SliderFloat("Damage Multiplier", &weapons.damageMult, 1.f, 10.f);
            ImGui::SliderFloat("Range Multiplier", &weapons.rangeMult, 1.f, 1000.f);
            ImGui::Checkbox("Rapid Fire", &weapons.rapidFire);
            ImGui::Checkbox("Fire Bullets", &weapons.fireBullets);
            ImGui::Checkbox("Teleport Bullets", &weapons.teleportBullets);
            ImGui::Combo("Weapon Skin", &weapons.skin, "Default\0Gold\0Platinum\0Diamond\0");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Misc")) {
            ImGui::Checkbox("Crosshair", &misc.crosshair);
            ImGui::ColorEdit3("Crosshair Color", misc.crosshairColor);
            ImGui::ColorEdit3("Menu Color", misc.menuColor);
            ImGui::Checkbox("Freecam", &misc.freecam);
            ImGui::SliderFloat("NoClip Speed", &misc.noclipSpeed, 1.f, 50.f);
            ImGui::SliderFloat("Altitude", &misc.altitude, 0.f, 500.f);
            ImGui::SliderInt("Health Override", &misc.hp, 0, 400);
            ImGui::SliderInt("Armor Override", &misc.armor, 0, 400);
            ImGui::SliderInt("Time of Day", &misc.time, 0, 23);
            ImGui::SliderInt("Weather Type", &misc.weather, 0, 12);
            ImGui::Checkbox("Auto Heal", &misc.autoHeal);
            ImGui::Checkbox("Auto Armor", &misc.autoArmor);
            ImGui::Checkbox("Disable HUD", &misc.disableHud);
            ImGui::Checkbox("Show FPS", &misc.showFps);
            ImGui::SliderFloat("Game Speed", &misc.gameSpeed, 0.1f, 2.f);

            ImGui::SeparatorText("Reverse Natives");
            static char nativeHashInput[32] = "";
            static char nativeArgsInput[128] = "";
            static char nativeResult[128] = "";
            ImGui::InputText("Native Hash (hex)", nativeHashInput, IM_ARRAYSIZE(nativeHashInput));
            ImGui::InputText("Arguments (comma sep)", nativeArgsInput, IM_ARRAYSIZE(nativeArgsInput));
            if (ImGui::Button("Call Native")) {
                // TODO: Appeler la native avec le hash et les arguments (stub)
                // snprintf(nativeResult, sizeof(nativeResult), "Résultat: 0x%X", 0x12345678);
                strcpy(nativeResult, "Résultat: (stub)");
            }
            ImGui::Text("%s", nativeResult);

            ImGui::SeparatorText("FiveM Offsets");
            static uintptr_t replayInterface = 0x1F2A3B40;
            static uintptr_t worldPtr        = 0x23C5A8B0;
            static uintptr_t playerList      = 0x1C3B2F10;
            static uintptr_t blipList        = 0x1F4A7C20;
            static uintptr_t cameraPtr       = 0x1B2C4D30;
            ImGui::InputScalar("Replay Interface", ImGuiDataType_U64, &replayInterface, NULL, NULL, "%p", ImGuiInputTextFlags_ReadOnly);
            ImGui::InputScalar("World Pointer", ImGuiDataType_U64, &worldPtr, NULL, NULL, "%p", ImGuiInputTextFlags_ReadOnly);
            ImGui::InputScalar("Player List", ImGuiDataType_U64, &playerList, NULL, NULL, "%p", ImGuiInputTextFlags_ReadOnly);
            ImGui::InputScalar("Blip List", ImGuiDataType_U64, &blipList, NULL, NULL, "%p", ImGuiInputTextFlags_ReadOnly);
            ImGui::InputScalar("Camera Ptr", ImGuiDataType_U64, &cameraPtr, NULL, NULL, "%p", ImGuiInputTextFlags_ReadOnly);
            if (ImGui::Button("Copier tous les offsets")) {
                // TODO: Copier les offsets dans le presse-papier (stub)
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Events")) {
            ImGui::Checkbox("Stop All Resources", &events.stopAll);
            ImGui::Checkbox("Log Events", &events.logEvents);
            ImGui::Checkbox("Re-run Last Event", &events.rerun);
            ImGui::InputText("Execute Event Name", events.customEvent, IM_ARRAYSIZE(events.customEvent));
            if (ImGui::Button("Run Custom Event")) {
                events.execute = true;
            }
            ImGui::SeparatorText("Event Tools");
            ImGui::InputInt("Event ID", &events.eventId);
            if (ImGui::Button("Send Event by ID")) { events.sendById = true; }
            ImGui::Checkbox("Block All Events", &events.blockAll);
            ImGui::Checkbox("Spam Event", &events.spamEvent);
            ImGui::SliderInt("Spam Count", &events.spamCount, 1, 100);
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
