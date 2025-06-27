#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "Settings.hpp" // Contient toutes les variables + load/save

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

LPDIRECT3D9 g_pD3D = nullptr;
LPDIRECT3DDEVICE9 g_pd3dDevice = nullptr;
D3DPRESENT_PARAMETERS g_d3dpp = {};
HWND hwnd = nullptr;
bool showMenu = true;

void InitD3D(HWND hWnd) {
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.hDeviceWindow = hWnd;

    g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice);
}

void CleanD3D() {
    if (g_pd3dDevice) g_pd3dDevice->Release();
    if (g_pD3D) g_pD3D->Release();
}

void RenderMenu() {
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(menuColor[0], menuColor[1], menuColor[2], menuColor[3]));
    ImGui::Begin("FiveM Trainer", &showMenu, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::BeginTabBar("MainTabs")) {
        if (ImGui::BeginTabItem("Aim Assist")) {
            ImGui::Checkbox("Enable", &aimAssistEnabled);
            if (aimAssistEnabled) {
                ImGui::SliderFloat("Smoothing", &aimSmoothing, 0.1f, 5.0f);
                ImGui::SliderFloat("FOV", &aimFov, 10.0f, 180.0f);
                ImGui::Checkbox("On Key", &aimOnKey);
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Weapons")) {
            ImGui::Checkbox("Infinite Ammo", &infiniteAmmo);
            ImGui::Checkbox("Max Damage", &infiniteDamage);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Visuals")) {
            ImGui::Checkbox("Box", &boxEnabled);
            ImGui::Checkbox("Skeleton", &skeletonEnabled);
            ImGui::Checkbox("Distance", &distanceEnabled);
            ImGui::Checkbox("Name", &nameEnabled);
            ImGui::Checkbox("Weapon ESP", &weaponEnabled);
            ImGui::Checkbox("Health", &healthEnabled);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Vehicle")) {
            ImGui::Checkbox("Godmode", &vehicleGodmode);
            ImGui::Checkbox("Demi-Godmode", &vehicleDemiGodmode);
            ImGui::Checkbox("Force Engine", &forceEngine);
            ImGui::Checkbox("Repair Instant", &repairVehicle);
            ImGui::Checkbox("Rocket Boost", &rocketBoost);
            ImGui::Checkbox("Parachute Car", &parachute);
            ImGui::Checkbox("Jumping", &jumping);
            ImGui::Checkbox("Ramming Mode", &ramming);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Player")) {
            ImGui::Checkbox("Godmode", &playerGodmode);
            ImGui::Checkbox("Demi-Godmode", &playerDemiGodmode);
            ImGui::Checkbox("Regenerate Armor", &regenerateArmor);
            ImGui::Checkbox("Force Wanted Level", &forceWantedLevel);
            ImGui::SliderFloat("Swim Speed", &swimSpeed, 1.0f, 10.0f);
            ImGui::Checkbox("No Collision", &noCollision);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Misc")) {
            ImGui::Checkbox("Enable Crosshair", &crosshairEnabled);
            ImGui::ColorEdit3("Crosshair Color", crosshairColor);
            ImGui::ColorEdit4("Menu Color", menuColor);
            if (ImGui::Button("Save Config")) SaveConfig("config.json");
            if (ImGui::Button("Load Config")) LoadConfig("config.json");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
    ImGui::PopStyleColor();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    if (msg == WM_KEYUP && wParam == VK_INSERT)
        showMenu = !showMenu;
    if (msg == WM_DESTROY)
        PostQuitMessage(0);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"FiveMCheatWindow";
    RegisterClass(&wc);

    hwnd = CreateWindowW(wc.lpszClassName, L"FiveMCheat Trainer by youness",
        WS_OVERLAPPEDWINDOW, 200, 200, 900, 600, nullptr, nullptr, hInstance, nullptr);

    InitD3D(hwnd);
    ShowWindow(hwnd, nCmdShow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    LoadConfig("config.json");

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplWin32_NewFrame();
        ImGui_ImplDX9_NewFrame();
        ImGui::NewFrame();

        if (showMenu)
            RenderMenu();

        ImGui::EndFrame();
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
            D3DCOLOR_RGBA(10, 10, 10, 255), 1.0f, 0);
        g_pd3dDevice->BeginScene();

        if (crosshairEnabled) {
            D3DVIEWPORT9 vp;
            g_pd3dDevice->GetViewport(&vp);
            int cx = vp.Width / 2, cy = vp.Height / 2;
            D3DRECT h = { cx - 5, cy, cx + 5, cy + 1 };
            D3DRECT v = { cx, cy - 5, cx + 1, cy + 5 };
            g_pd3dDevice->Clear(1, &h, D3DCLEAR_TARGET,
                D3DCOLOR_COLORVALUE(crosshairColor[0], crosshairColor[1], crosshairColor[2], 1.0f), 1.0f, 0);
            g_pd3dDevice->Clear(1, &v, D3DCLEAR_TARGET,
                D3DCOLOR_COLORVALUE(crosshairColor[0], crosshairColor[1], crosshairColor[2], 1.0f), 1.0f, 0);
        }

        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        g_pd3dDevice->EndScene();
        g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
    }

    SaveConfig("config.json");

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanD3D();
    return 0;
}