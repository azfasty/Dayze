// Fichier : DayzeInjector.cpp

#include <windows.h>
#include "imgui.h"
#include "Functions.h"

// Déclaration de la fonction ShowDayzeMenu()
void ShowDayzeMenu();

// Fonction principale pour une application Windows GUI
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Création d'une fenêtre Windows (exemple basique)
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "DayzeInjectorClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "DayzeInjectorClass", "Dayze Injector", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Initialisation ImGui
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

    // Nettoyage ImGui
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
