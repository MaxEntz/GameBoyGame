/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** core.c
*/

#include "main/core.h"
#include "lobby/lobby.h"

static const management_state_t g_state_function[MAX_STATES] = {
    {GAME_STATE_LOBBY    ,lobby,handle_input_lobby,update_lobby},
    {GAME_STATE_PLAYING  ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_PAUSED   ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_VICTORY  ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_MG1      ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_MG2      ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_MG3      ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_GAME_OVER,NULL ,NULL              ,NULL}
};

static void
init_game(game_t *game)
{
    game->state = GAME_STATE_LOBBY;
    game->is_running = TRUE;
    game->state_changed = FALSE;
    game->player_x = 88;
    game->player_y = 78;
}

static void
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
    void (*loader)(game_t *game) = g_state_function[game->state].load_assets;

    if (loader != NULL)
        loader(game);
}

static void
change_scene(game_t *game)
{
    if (game->state_changed) {
        set_display(FALSE, FALSE, FALSE, FALSE);
        load_assets(game);
        set_display(TRUE, TRUE, TRUE, FALSE);
        game->state_changed = FALSE;
    }
}

static void
vbl_interrupt(void)
{
    // Cette fonctions est appelé a chaque frame
    // En gros, quand le processeur a terminé de dessiner l'écran de base
    // le temps qu'il remonte tout en haut de l'écran, il appelle cette fonction
    // Et dcp pour opti faut utiliser ce temps
    // On mettera les clock et tout ce qu'on a besoin ici
    // Attention le temps est court, faut pas faire n'importe quoi
    // genre des calculs de ouf, juste des trucs simple et rapide
}

static void
update_game(game_t *game)
{
    void (*updater)(game_t *game) = g_state_function[game->state].update;

    if (updater != NULL)
        updater(game);
}

static void
handle_keys(game_t *game)
{
    UINT8 keys = joypad();

    void (*handler)(game_t *game, UINT8 keys) =
        g_state_function[game->state].handle_input;
    
    if (handler != NULL)
        handler(game, keys);
}

void
core(void)
{
    game_t game;

    init_game(&game);
    add_VBL(vbl_interrupt);
    enable_interrupts();
    set_display(FALSE, FALSE, FALSE, FALSE);
    load_assets(&game);
    set_display(TRUE, TRUE, TRUE, FALSE);
    while (game.is_running) {
        wait_vbl_done();
        change_scene(&game);
        handle_keys(&game);
        update_game(&game);
    }
}
