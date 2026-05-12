/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tm_handle_input.c
*/

#include "mg1/trap_memory.h"

void
handle_input_trap_memory(OUT game_t *game,
                        IN UINT8 keys)
{
    (void)game;
    trap_memory_t *tm = trap_memory_get();

    if (keys & J_LEFT) {
        tm->player_x -= SPEED;
        tm->is_moving = TRUE;
        tm->moving_dir = MOVING_SENS_LEFT;
    }
    if (keys & J_RIGHT) {
        tm->player_x += SPEED;
        tm->is_moving = TRUE;
        tm->moving_dir = MOVING_SENS_RIGHT;
    }
    if (keys & J_UP) {
        tm->player_y -= SPEED;
        tm->is_moving = TRUE;
        tm->moving_dir = MOVING_SENS_UP;
    }
    if (keys & J_DOWN) {
        tm->player_y += SPEED;
        tm->is_moving = TRUE;
        tm->moving_dir = MOVING_SENS_DOWN;
    }
}
