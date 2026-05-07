/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** transition_map_lobby.c
*/

#include "lobby/lobby.h"

void
transition_map_animation(OUT game_t *game,
                         IN transition_dir_t dir)
{
    lobby_state_t *lobby = lobby_get_state();
    INT16 x = lobby->player_x - 8;
    INT16 y = lobby->player_y - 16;

    set_bkg_tiles(0, 0, 20, 18, transition_map);
    while (lobby->is_changing_map) {
        if (dir == TRANSITION_LR) {
            if (x >= 160 - 24)
                lobby->is_changing_map = FALSE;
            else
                x += 2;
        } else if (dir == TRANSITION_RL) {
            if (x <= 16)
                lobby->is_changing_map = FALSE;
            else
                x -= 2;
        } else if (dir == TRANSITION_TB) {
            if (y >= 144 - 24)
                lobby->is_changing_map = FALSE;
            else
                y += 2;
        } else if (dir == TRANSITION_BT) {
            if (y <= 16)
                lobby->is_changing_map = FALSE;
            else
                y -= 2;
        }
        move_sprite(0, x + 8, y + 16);
        move_sprite(1, x + 16, y + 16);
        move_sprite(2, x + 8, y + 24);
        move_sprite(3, x + 16, y + 24);
        wait_vbl_done();
    }
    lobby->player_x = x + 8;
    lobby->player_y = y + 16;
    set_bkg_tiles(0, 0, 20, 18, lobby->current_map);

    (void)game;
}
