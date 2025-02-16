#include <windows.h>
#include "imgui.h"
#include "Functions.h"

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
