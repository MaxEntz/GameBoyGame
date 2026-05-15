/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** save_select.c
*/

#include "menu/save_select.h"

void
save_select(OUT game_t *game)
{
    (void)game;
    set_bkg_data(0, 1, void_tile);
    set_bkg_tiles(0, 0, 20, 18, save_select_map);
}

void
handle_input_save_select(OUT game_t *game,
                        IN UINT8 keys)
{    
    if (keys & J_START)
        game_changer(game, GAME_STATE_LOBBY, TRUE);
}

void
update_save_select(OUT game_t *game)
{
    (void)game;
}
