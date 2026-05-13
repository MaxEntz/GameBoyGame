/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** core.c
*/

#include "main/core.h"
#include "common/text_renderer.h"
#include "common/dialogue.h"
#include "lobby/lobby.h"
#include "mg2/tetris.h"
#include "menu/menu.h"
#include "mg3/mg3.h"

/**
 * @brief Array of function pointers to handle different game states
 */
static const management_state_t g_state_function[MAX_STATES] = {
    {GAME_STATE_LOBBY    ,lobby,handle_input_lobby,update_lobby},
    {GAME_STATE_PLAYING  ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_PAUSED   ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_VICTORY  ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_MG1      ,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_MG2      ,tetris ,handle_input_tetris,update_tetris}        ,
    {GAME_STATE_MG3      ,flappybird, handle_input_flappybird, update_flappybird}        ,
    {GAME_STATE_GAME_OVER,NULL ,NULL              ,NULL}        ,
    {GAME_STATE_MENU     ,menu ,handle_input_menu ,update_menu}
};

static void
init_game(OUT game_t *game)
{
    game->state = GAME_STATE_MENU;
    game->is_running = TRUE;
    game->state_changed = FALSE;
    game->best_score_mg1 = MASTER_SCORE_MG1;
    game->best_score_mg2 = MASTER_SCORE_MG2;        //a changer dans save
    game->best_score_mg3 = MASTER_SCORE_MG3;
    game->score_mg1 = 0;
    game->score_mg2 = 0;
    game->score_mg3 = 0;
    game->level = 1;
}


/**
 * @brief Set the display configuration
 * @param display Whether to turn on the display
 * @param sprite Whether to show sprites
 * @param bkg Whether to show the background
 * @param win Whether to show the window layer
 * @return void
 */
static void
set_display(IN BOOLEAN display,
            IN BOOLEAN sprite,
            IN BOOLEAN bkg,
            IN BOOLEAN win)
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

/**
 * @brief Load the assets for the current game state
 */
static void
load_assets(OUT game_t *game)
{
    void (*loader)(game_t *game) = g_state_function[game->state].load_assets;

    if (loader != NULL)
        loader(game);
}

void
change_scene(OUT game_t *game)
{
    if (game->state_changed) {
        set_display(FALSE, FALSE, FALSE, FALSE);
        load_assets(game);
        set_display(TRUE, TRUE, TRUE, FALSE);
        game->state_changed = FALSE;
    }
}

/**
 * @brief Update the game state
 */
static void
update_game(OUT game_t *game)
{
    void (*updater)(game_t *game) = g_state_function[game->state].update;
    
    if (updater != NULL)
        updater(game);
}

/**
 * @brief Handle the input for the current game state
 */
static void
handle_keys(OUT game_t *game)
{
    UINT8 keys = joypad();

    void (*handler)(game_t *game, UINT8 keys) =
    g_state_function[game->state].handle_input;

    if (handler != NULL)
        handler(game, keys);
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

void
core(void)
{
    game_t game;

    init_game(&game);
    text_renderer_init();
    dialogue_init();
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
