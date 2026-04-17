/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lobby.c
*/

#include "lobby/lobby.h"

static void
load_assets(void)
{
    set_bkg_data(0, 1, grass_tile);
    set_bkg_data(1, 1, wall_tile);
    set_bkg_tiles(0, 0, 20, 18, map);
    set_sprite_data(0, 1, square_tile);
    set_sprite_tile(0, 0);
}

void
lobby(game_t *game)
{
    if (game->state_changed) {
        load_assets();
        game->state_changed = FALSE;
    }
}
