typedef struct TitleState TitleState;
struct TitleState
{
    b32 settings_menu_open;
    SettingsMenu settings_menu;
};

internal void
TitleStateInit(TitleState *state)
{
    state->settings_menu_open = 0;
}

internal void
TitleStateCleanUp(TitleState *state)
{
    
}

internal StateType
TitleStateUpdate(TitleState *state)
{
    StateType next_state = STATE_invalid;
    
    if(state->settings_menu_open)
    {
        state->settings_menu_open = SettingsMenuUpdate(&state->settings_menu);
    }
    else
    {
        UIPushCenteredColumn(&app->ui, v2(400, 50), 5);
        {
            UITitle(&app->ui, "DUNGEONEER");
            UIDivider(&app->ui);
            
            if(UIButton(&app->ui, "Play"))
            {
                next_state = STATE_game;
            }
            if(UIButton(&app->ui, "Settings"))
            {
                state->settings_menu_open = 1;
                state->settings_menu.state = SETTINGS_MENU_main;
            }
            if(UIButton(&app->ui, "Quit"))
            {
                platform->quit = 1;
            }
        }
        UIPopColumn(&app->ui);
    }
    
    return next_state;
}