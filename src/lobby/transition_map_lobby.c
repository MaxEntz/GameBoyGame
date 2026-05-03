/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** transition_map_lobby.c
*/

#include "lobby/lobby.h"

void
transition_map_animation(OUT game_t *game)
{
    INT16 x = game->player_x - 8;
    INT16 y = game->player_y - 16;
    transition_dir_t dir = TRANSITION_TB;

    set_bkg_tiles(0, 0, 20, 18, transition_map);
    if (x == 0) {
        dir = TRANSITION_LR;
        y += 16;
    } else if (x == 160 - 16) {
        dir = TRANSITION_RL;
        y += 16;
    } else if (y == 0) {
        dir = TRANSITION_TB;
        x += 8;
    } else if (y == 144 - 16) {
        dir = TRANSITION_BT;
        x += 8;
    }
    while (game->is_changing_map) {
        if (dir == TRANSITION_LR) {
            if (x >= 160 - 16)
                game->is_changing_map = FALSE;
            else
                x += 2;
        } else if (dir == TRANSITION_RL) {
            if (x <= 0)
                game->is_changing_map = FALSE;
            else
            x -= 2;
        } else if (dir == TRANSITION_TB) {
            if (y >= 144)
                game->is_changing_map = FALSE;
            else
                y += 2;
        } else if (dir == TRANSITION_BT) {
            if (y <= 0)
                game->is_changing_map = FALSE;
            else
                y -= 2;
        }
        move_sprite(0, x, y);
        move_sprite(1, x + 8, y);
        move_sprite(2, x, y + 8);
        move_sprite(3, x + 8, y + 8);
        wait_vbl_done();
    }
    game->player_x = x;
    game->player_y = y;
    set_bkg_tiles(0, 0, 20, 18, game->current_map);
    return;
}
