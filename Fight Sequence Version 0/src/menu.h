#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "types.h"

#include <vector>
#include <string>

class Menu
{
public:
    Menu();

    // Update keyboard input
    void Update();
    // Draw menu
    void Draw();
    // Change menu screen
    void SetScreen(MenuScreen screen);
    // Get current screen
    MenuScreen GetScreen() const;
    // Get selected action
    MenuAction GetAction();
    // Reset action
    void ClearAction();
    // Open pause menu
    void OpenPauseMenu();
    // Settings values
    float musicVolume;
    float sfxVolume;

    bool fullscreen;

private:

    MenuScreen currentScreen;
    MenuAction currentAction;

    // Currently selected item
    int selectedItem;

    // Menu options
    std::vector<std::string> items;

    // Load menu contents
    void LoadMainMenu();
    void LoadOptionsMenu();
    void LoadTutorialMenu();
    void LoadCreditsMenu();
    void LoadSettingsMenu();
    void LoadScoreboardMenu();
    void LoadPauseMenu();

    // Handle ENTER selection
    void SelectItem();

    // Drawing helpers
    void DrawTitle();
    void DrawItems();
};


#endif
