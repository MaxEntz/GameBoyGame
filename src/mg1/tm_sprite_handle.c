/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tm_sprite_handle.c
*/

#include "mg1/trap_memory.h"

void
move_sprite_personage(OUT trap_memory_t *game)
{
    UINT8 sens = game->moving_dir;

    if (game->is_moving) {
        set_sprite_tile(0, sens + 0);
        set_sprite_tile(1, sens + 1);
        if (game->fps_counter < 15 || (game->fps_counter > 30 && game->fps_counter < 45)) {
            set_sprite_tile(2, sens + 4);
            set_sprite_tile(3, sens + 3);
        }
        else if (game->fps_counter < 30 || (game->fps_counter > 45 && game->fps_counter < 60)) {
            set_sprite_tile(2, sens + 2);
            set_sprite_tile(3, sens + 5);
        }
    } else {
        set_sprite_tile(0, sens + 0);
        set_sprite_tile(1, sens + 1);
        set_sprite_tile(2, sens + 2);
        set_sprite_tile(3, sens + 3);
    }
    game->is_moving = FALSE;
}
