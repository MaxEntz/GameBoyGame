/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tm_handle_input.c
*/

#include "mg1/trap_memory.h"

/**
 * @brief Check if the player is colliding with a wall in the given direction
 * @param game Pointer to the game structure
 * @param sens The direction of movement (left, right, up, down)
 * @return TRUE if colliding with a wall, FALSE otherwise
 */
static BOOLEAN
is_colliding_with_wall(IN game_t *game,
                       IN UINT8 sens)
{
    (void)game;
    trap_memory_t *tm = trap_memory_get();
    INT16 x = tm->player_x - 8;
    INT16 y = tm->player_y - 16;
    UINT8 tile = 0;

    switch (sens) {
        case MOVING_SENS_LEFT:
            x -= SPEED;
            y += 8;
            break;
        case MOVING_SENS_RIGHT:
            x += SPEED + 16;
            y += 8;
            break;
        case MOVING_SENS_UP:
            x += 8;
            y -= SPEED;
            break;
        case MOVING_SENS_DOWN:
            x += 8;
            y += SPEED + 16;
            break;
        default:
            break;
    }

    if (x < 0 || y < 0 || x >= 160 || y >= 144)
        return TRUE;
    tile = get_tile_by_map(tm->current_map, x, y);
    if (tile == 0 || tile == 1 || tile == 14 ||
        tile == 0 + OFFSET_SAFER_TILE || tile == 1 + OFFSET_SAFER_TILE)
        return FALSE;
    return TRUE;
}

void
handle_input_trap_memory(OUT game_t *game,
                        IN UINT8 keys)
{
    (void)game;
    trap_memory_t *tm = trap_memory_get();

    if (keys & J_LEFT && !is_colliding_with_wall(game, MOVING_SENS_LEFT)) {
        tm->player_x -= SPEED;
        tm->is_moving = TRUE;
        tm->moving_dir = MOVING_SENS_LEFT;
    }
    if (keys & J_RIGHT && !is_colliding_with_wall(game, MOVING_SENS_RIGHT)) {
        tm->player_x += SPEED;
        tm->is_moving = TRUE;
        tm->moving_dir = MOVING_SENS_RIGHT;
    }
    if (keys & J_UP && !is_colliding_with_wall(game, MOVING_SENS_UP)) {
        tm->player_y -= SPEED;
        tm->is_moving = TRUE;
        tm->moving_dir = MOVING_SENS_UP;
    }
    if (keys & J_DOWN && !is_colliding_with_wall(game, MOVING_SENS_DOWN)) {
        tm->player_y += SPEED;
        tm->is_moving = TRUE;
        tm->moving_dir = MOVING_SENS_DOWN;
    }
}
