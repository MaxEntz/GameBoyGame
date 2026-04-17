/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** core.c
*/

#include "main/core.h"
#include "lobby/lobby.h"

static const asset_loading_t asset_loaders[MAX_STATES] = {
    {GAME_STATE_LOBBY, lobby},
    {GAME_STATE_PLAYING, NULL},
    {GAME_STATE_PAUSED, NULL},
    {GAME_STATE_VICTORY, NULL},
    {GAME_STATE_MG1, NULL},
    {GAME_STATE_MG2, NULL},
    {GAME_STATE_MG3, NULL},
    {GAME_STATE_GAME_OVER, NULL}
};

static void
init_game(game_t *game)
{
    game->state = GAME_STATE_LOBBY;
    game->is_running = TRUE;
    game->state_changed = FALSE;
}

void
set_display(BOOLEAN display,
            BOOLEAN sprite,
            BOOLEAN bkg,
            BOOLEAN win)
{
    if (display)
        DISPLAY_ON;
    else
        DISPLAY_OFF;
    if (sprite)
        SHOW_SPRITES;
    else
        HIDE_SPRITES;
    if (bkg)
        SHOW_BKG;
    else
        HIDE_BKG;
    if (win)
        SHOW_WIN;
    else
        HIDE_WIN;
}

static void
load_assets(game_t *game)
{
    void (*loader)(game_t *game) = NULL;

    for (UINT8 i = 0; i < MAX_STATES; i++) {
        if (asset_loaders[i].state == game->state) {
            loader = asset_loaders[i].load_assets;
            break;
        }
    }
    if (loader != NULL)
        loader(game);
}

static void
change_scene(game_t *game)
{
    if (game->state_changed) {
        load_assets(game);
        game->state_changed = FALSE;
    }
}

void
core(void)
{
    game_t game;
    UINT8 x = 76;
    UINT8 y = 68;

    init_game(&game);
    set_display(FALSE, FALSE, FALSE, FALSE);
    load_assets(&game);
    set_display(TRUE, TRUE, TRUE, FALSE);
    while (game.is_running) {
        UINT8 keys = joypad();

        change_scene(&game);
        if ((keys & J_UP)    && y > 8)           y -= SPEED;
        if ((keys & J_DOWN)  && y < 144 - 16)    y += SPEED;
        if ((keys & J_LEFT)  && x > 8)           x -= SPEED;
        if ((keys & J_RIGHT) && x < 160 - 16)    x += SPEED;
        move_sprite(0, x + 8, y + 16);
        delay(50);
        vsync();
    }
}
