/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tm_sprite_handle.c
*/

#include "mg1/trap_memory.h"

/**
 * @brief Move the player sprite based on the current movement state
 * @param game Pointer to the game structure
 * @return void
 */
void
move_sprite_personage(OUT trap_memory_t *game)
{
    UINT8 sens = game->moving_dir;

    if (game->is_moving) {
        set_sprite_tile(0, sens + 0);
        set_sprite_tile(1, sens + 1);
        if (game->fps_counter < 15) {
            set_sprite_tile(2, sens + 4);
            set_sprite_tile(3, sens + 3);
        }
        else if (game->fps_counter < 30) {
            set_sprite_tile(2, sens + 2);
            set_sprite_tile(3, sens + 5);
        } else
            game->fps_counter = 0;
    } else {
        set_sprite_tile(0, sens + 0);
        set_sprite_tile(1, sens + 1);
        set_sprite_tile(2, sens + 2);
        set_sprite_tile(3, sens + 3);
    }
    game->is_moving = FALSE;
}