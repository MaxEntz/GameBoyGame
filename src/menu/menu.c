/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** menu.c
*/

#include "menu/menu.h"
#include "common/game_changer.h"

/**
 * @brief Clear the background layer to a blank state
 */
static void
clear_background(void)
{
    fill_bkg_rect(0, 0, COMMON_SCREEN_WIDTH_TILES, COMMON_SCREEN_HEIGHT_TILES, 0);
}

void
menu(OUT game_t *game)
{
    (void)game;
    clear_background();
}

void
handle_input_menu(OUT game_t *game,
                  IN UINT8 keys)
{
    if (keys & J_A)
        game_changer(game, GAME_STATE_LOBBY);
}

void
update_menu(OUT game_t *game)
{
    (void)game;
}
