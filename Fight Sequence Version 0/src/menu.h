#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include <vector>
#include <string>

// Different screens inside the menu system
enum class MenuScreen
{
    MAIN_MENU,
    OPTIONS,
    SETTINGS,
    SCOREBOARD,
    PAUSE_MENU
};


// Actions that the Game class will receive
enum class MenuAction
{
    NONE,

    // Main menu actions
    NEW_GAME,
    CONTINUE_GAME,
    OPEN_OPTIONS,
    OPEN_SETTINGS,
    OPEN_SCOREBOARD,
    QUIT_GAME,

    // Options actions
    SHOW_CONTROLS,
    SHOW_TUTORIAL,
    SHOW_CREDITS,

    // Settings actions
    CHANGE_MUSIC_VOLUME,
    CHANGE_SFX_VOLUME,
    TOGGLE_FULLSCREEN,

    // Pause menu actions
    RESUME_GAME,
    RESTART_GAME,
    EXIT_TO_MAIN_MENU
};

class Menu
{

public:

    Menu();


    // Update menu input
    void Update();
    // Draw menu on screen
    void Draw();
    // Change between menus
    void SetScreen(MenuScreen screen);
    // Get current menu
    MenuScreen GetScreen() const;
    // Get what player selected
    MenuAction GetAction();
    // Reset action after Game handles it
    void ClearAction();
    // Used by Game when player presses pause
    void OpenPauseMenu();
    // Settings values

    float musicVolume;
    float sfxVolume;

    bool fullscreen;

private:
    MenuScreen currentScreen;
    MenuAction currentAction;

    // Current selected option
    int selectedItem;

    // Items displayed in current menu
    std::vector<std::string> items;

    // Load menu contents

    void LoadMainMenu();

    void LoadOptionsMenu();

    void LoadSettingsMenu();

    void LoadScoreboardMenu();

    void LoadPauseMenu();

    // Handle selection

    void SelectItem();

    // Draw helpers

    void DrawTitle();

    void DrawItems();

};

#endif
