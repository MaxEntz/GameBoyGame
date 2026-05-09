/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** menu.c
*/

#include "menu/menu.h"
#include "common/game_changer.h"
#include "common/vram_clear.h"

void
menu(OUT game_t *game)
{
    (void)game;
    vram_clear();
    set_bkg_data(0, MENU_BG_TILE_COUNT, menu_bg_tiles);
    set_bkg_tiles(0, 0, 20, 18, menu_bg_map);
}

void
handle_input_menu(OUT game_t *game,
                  IN UINT8 keys)
{
    if (keys & J_START)
        game_changer(game, GAME_STATE_LOBBY);
}

void
update_menu(OUT game_t *game)
{
    (void)game;
}
