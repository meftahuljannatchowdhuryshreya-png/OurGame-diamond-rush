#include "menu.h"

Menu::Menu()
{
    currentScreen = MenuScreen::MAIN_MENU;
    currentAction = MenuAction::NONE;
    selectedItem = 0;

    musicVolume = 80;
    sfxVolume = 80;
  
    fullscreen = false;

    LoadMainMenu();
}

void Menu::SetScreen(MenuScreen screen)
{
    currentScreen = screen;
    selectedItem = 0;

    switch(screen)
    {
        case MenuScreen::MAIN_MENU:
            LoadMainMenu();
            break;

        case MenuScreen::OPTIONS:
            LoadOptionsMenu();
            break;

        case MenuScreen::SETTINGS:
            LoadSettingsMenu();
            break;

        case MenuScreen::SCOREBOARD:
            LoadScoreboardMenu();
            break;

        case MenuScreen::PAUSE_MENU:
            LoadPauseMenu();
            break;
    }
}

MenuScreen Menu::GetScreen() const
{
    return currentScreen;
}

MenuAction Menu::GetAction()
{
    return currentAction;
}

void Menu::ClearAction()
{
    currentAction = MenuAction::NONE;
}

void Menu::OpenPauseMenu()
{
    SetScreen(MenuScreen::PAUSE_MENU);
}

void Menu::LoadMainMenu()
{
    items =
    {
        "New Game",
        "Continue",
        "Options",
        "Settings",
        "Scoreboard",
        "Quit Game"
    };
}

void Menu::LoadOptionsMenu()
{
    items =
    {
        "Controls",
        "Tutorial",
        "Credits",
        "Back"
    };
}

void Menu::LoadSettingsMenu()
{
    items =
    {
        "Music Volume",
        "SFX Volume",
        "Fullscreen",
        "Back"
    };
}

void Menu::LoadScoreboardMenu()
{
    items =
    {
        "Back"
    };
}

void Menu::LoadPauseMenu()
{
    items =
    {
        "Resume",
        "Restart",
        "Settings",
        "Exit To Main Menu"
    };
}

void Menu::Update()
{
 // Move selection
    if(IsKeyPressed(KEY_DOWN))
    {
        selectedItem++;

        if(selectedItem >= items.size())
            selectedItem = 0;
    }

    if(IsKeyPressed(KEY_UP))
    {
        selectedItem--;

        if(selectedItem < 0)
            selectedItem = items.size()-1;
    }

    // Settings controls

    if(currentScreen == MenuScreen::SETTINGS)
    {
        if(selectedItem == 0)
        {
            if(IsKeyPressed(KEY_RIGHT))
            {
                musicVolume += 10;

                if(musicVolume > 100)
                    musicVolume = 100;
            }

            if(IsKeyPressed(KEY_LEFT))
            {
                musicVolume -= 10;

                if(musicVolume < 0)
                    musicVolume = 0;
            }
        }

        if(selectedItem == 1)
        {
            if(IsKeyPressed(KEY_RIGHT))
            {
                sfxVolume += 10;

                if(sfxVolume > 100)
                    sfxVolume = 100;
            }

            if(IsKeyPressed(KEY_LEFT))
            {
                sfxVolume -= 10;

                if(sfxVolume < 0)
                    sfxVolume = 0;
            }
        }

        if(selectedItem == 2)
        {
            if(IsKeyPressed(KEY_ENTER))
            {
                fullscreen = !fullscreen;

                ToggleFullscreen();
            }
        }

    }

    if(IsKeyPressed(KEY_ENTER))
    {
        SelectItem();
    }

    // Escape goes back
    if(IsKeyPressed(KEY_ESCAPE))
    {

        if(currentScreen != MenuScreen::MAIN_MENU)
        {
            SetScreen(MenuScreen::MAIN_MENU);
        }
    }
}

void Menu::SelectItem()
{

    std::string choice = items[selectedItem];

    // MAIN MENU
    if(choice == "New Game")
    {
        currentAction = MenuAction::NEW_GAME;
    }

    else if(choice == "Continue")
    {
        currentAction = MenuAction::CONTINUE_GAME;
    }

    else if(choice == "Options")
    {
        SetScreen(MenuScreen::OPTIONS);
    }

    else if(choice == "Settings")
    {
        SetScreen(MenuScreen::SETTINGS);
    }

    else if(choice == "Scoreboard")
    {
        SetScreen(MenuScreen::SCOREBOARD);
    }

    else if(choice == "Quit Game")
    {
        currentAction = MenuAction::QUIT_GAME;
    }

    // OPTIONS

    else if(choice == "Controls")
    {
        currentAction = MenuAction::SHOW_CONTROLS;
    }

    else if(choice == "Tutorial")
    {
        currentAction = MenuAction::SHOW_TUTORIAL;
    }

    else if(choice == "Credits")
    {
        currentAction = MenuAction::SHOW_CREDITS;
    }

    // PAUSE MENU

    else if(choice == "Resume")
    {
        currentAction = MenuAction::RESUME_GAME;
    }

    else if(choice == "Restart")
    {
        currentAction = MenuAction::RESTART_GAME;
    }

    else if(choice == "Exit To Main Menu")
    {
        currentAction = MenuAction::EXIT_TO_MAIN_MENU;
    }

    // BACK

    else if(choice == "Back")
    {
        SetScreen(MenuScreen::MAIN_MENU);
    }

}

void Menu::Draw()
{
    ClearBackground(BLACK);
    DrawTitle();
    DrawItems();
}



void Menu::DrawTitle()
{
    DrawText(
        "ADVENTURE GAME",
        260,
        80,
        40,
        GOLD
    );
}



void Menu::DrawItems()
{
    int startY = 180;
    for(int i = 0; i < items.size(); i++)
    {
        Color color = WHITE;
        if(i == selectedItem)
            color = YELLOW;

        std::string text = items[i];

        // Display settings values

        if(currentScreen == MenuScreen::SETTINGS)
        {
            if(i == 0)
            {
                text += " : " 
                + std::to_string((int)musicVolume);
            }

            if(i == 1)
            {
                text += " : "
                + std::to_string((int)sfxVolume);
            }

            if(i == 2)
            {
                if(fullscreen)
                    text += " : ON";
                else
                    text += " : OFF";
            }
        }

        DrawText(
            text.c_str(),
            330,
            startY + i*50,
            30,
            color
        );
    }



    DrawText(
        "UP/DOWN : Select",
        20,
        650,
        20,
        LIGHTGRAY
    );

    DrawText(
        "ENTER : Confirm",
        20,
        680,
        20,
        LIGHTGRAY
    );
}
