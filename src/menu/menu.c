/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** menu.c
*/

#include "menu/menu.h"
#include "common/game_changer.h"

/**
 * @brief Load a blank tile into VRAM slot 0 and clear the background map
 */
static void
clear_background(void)
{
    set_bkg_data(0, 1, menu_void_tile);
    fill_bkg_rect(0, 0, COMMON_SCREEN_WIDTH_TILES, COMMON_SCREEN_HEIGHT_TILES, 0);
}

/**
 * @brief Move all player sprites off-screen (for when coming from lobby)
 */
static void
hide_sprites(void)
{
    UINT8 i = 0;

    for (i = 0; i < 4; i++)
        move_sprite(i, 0, 0);
}

void
menu(OUT game_t *game)
{
    (void)game;
    clear_background();
    hide_sprites();
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
