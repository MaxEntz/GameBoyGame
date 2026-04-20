/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lobby.c
*/

#include "lobby/lobby.h"
#include "common/game_changer.h"

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
lobby(OUT game_t *game)
{
    (void)game;
    load_assets();
}

void
update_lobby(OUT game_t *game)
{
    move_sprite(0, game->player_x, game->player_y);
}

void
handle_input_lobby(OUT game_t *game,
                   IN UINT8 keys)
{
    if (keys & J_A)
        game_changer(game, GAME_STATE_MG2);
    if (keys & J_LEFT && game->player_x > 8 + 16)
        game->player_x -= SPEED;
    if (keys & J_RIGHT && game->player_x < 168 - 16)
        game->player_x += SPEED;
    if (keys & J_UP && game->player_y > 8 + 16)
        game->player_y -= SPEED;
    if (keys & J_DOWN && game->player_y < 144 - 16)
        game->player_y += SPEED;
}
