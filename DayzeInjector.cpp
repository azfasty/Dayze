

// Fichier : DayzeInjector.cpp

#include <windows.h>
#include "imgui/imgui.h"

// Déclaration des fonctions externes
void EnableGodMode();
void EnableSpeedHack();
void EnableJumpPower();
void EnableInvisibility();
void RevivePlayer();
void HealPlayer();
void ExplodePlayer(int playerID);
void KillPlayer(int playerID);
void StealOutfit(int playerID);
void GiveWeapon();
void InfiniteAmmo();
void SpawnVehicle();
void RepairVehicle();
int GetPlayerCount();
const char* GetPlayerName(int index);

// Déclaration de la fonction ShowDayzeMenu()
void ShowDayzeMenu();

// Fonction principale Windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Définition de la classe de fenêtre
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"DayzeInjectorClass";

    RegisterClass(&wc);

    // Création de la fenêtre principale
    HWND hwnd = CreateWindowEx(0, L"DayzeInjectorClass", L"Dayze Injector", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Initialisation d'ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Boucle principale Windows
    MSG msg;
    bool running = true;
    while (running) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Démarrage de la frame ImGui
        ImGui::NewFrame();
        ShowDayzeMenu(); // Affichage du menu
        ImGui::Render();
    }

    // Nettoyage d'ImGui
    ImGui::DestroyContext();
    return 0;
}

// Affichage du menu ImGui
void ShowDayzeMenu() {
    ImGui::Begin("Dayze - GTA V / FiveM Cheat");

    if (ImGui::CollapsingHeader("SELF")) {
        if (ImGui::Button("GodMode")) EnableGodMode();
        if (ImGui::Button("Speedhack")) EnableSpeedHack();
        if (ImGui::Button("Jump Power")) EnableJumpPower();
        if (ImGui::Button("Invisible")) EnableInvisibility();
        if (ImGui::Button("Revive")) RevivePlayer();
        if (ImGui::Button("Heal")) HealPlayer();
    }

    if (ImGui::CollapsingHeader("ONLINE")) {
        static int selectedPlayer = 0;
        if (ImGui::BeginCombo("Liste Joueurs", "Sélectionner")) {
            for (int i = 0; i < GetPlayerCount(); i++) {
                if (ImGui::Selectable(GetPlayerName(i), selectedPlayer == i))
                    selectedPlayer = i;
            }
            ImGui::EndCombo();
        }
        if (ImGui::Button("Explode")) ExplodePlayer(selectedPlayer);
        if (ImGui::Button("Kill")) KillPlayer(selectedPlayer);
        if (ImGui::Button("Steal Outfit")) StealOutfit(selectedPlayer);
    }

    if (ImGui::CollapsingHeader("WEAPON")) {
        if (ImGui::Button("Give Weapon")) GiveWeapon();
        if (ImGui::Button("Infinite Ammo")) InfiniteAmmo();
    }

    if (ImGui::CollapsingHeader("VEHICLES")) {
        if (ImGui::Button("Spawn Vehicle")) SpawnVehicle();
        if (ImGui::Button("Repair")) RepairVehicle();
    }

    ImGui::End();
}
