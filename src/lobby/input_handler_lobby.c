/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** input_handler_lobby.c
*/

#include "lobby/lobby.h"
#include "common/random.h"

/**
 * @brief Get the tile at the specified position in the map
 * @param lobby Pointer to the lobby state
 * @param x X coordinate
 * @param y Y coordinate
 * @return The tile at the specified position
 */
static UINT8
get_tile_by_map(IN const lobby_state_t *lobby, INT16 x, INT16 y)
{
    UINT8 tile_x = 0;
    UINT8 tile_y = 0;

    if (x < 0 || y < 0)
        return 0;
    tile_x = x >> 3;
    tile_y = y >> 3;
    if (tile_x >= 20 || tile_y >= 18)
        return 0;
    return lobby->current_map[tile_y * 20 + tile_x];
}

/**
 * @brief Handle the A button input
 * @param game Pointer to the game structure
 */
static void
handle_a_input(IN game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();
    INT16 x = lobby->player_x - 8;
    INT16 y = lobby->player_y - 16;
    UINT8 tile = 0;

    if (x < 0 || y < 0)
        return;
    if (x >= 160 || y >= 144)
        return;
    switch (lobby->moving_dir) {
        case MOVING_SENS_UP:
            y -= 8;
            break;
        case MOVING_SENS_DOWN:
            y += 8;
            break;
        case MOVING_SENS_LEFT:
            x -= 8;
            break;
        case MOVING_SENS_RIGHT:
            x += 8;
            break;
        default:
            break;
    }
    tile = get_tile_by_map(lobby, x, y);
    if (tile == 23 || tile == 24 || tile == 25 || tile == 26)
        game_changer(game, GAME_STATE_MG2, TRUE);
    
}

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
    lobby_state_t *lobby = lobby_get_state();
    INT16 x = lobby->player_x - 8;
    INT16 y = lobby->player_y - 16;
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
    tile = get_tile_by_map(lobby, x, y);
    if (switch_map(game, x, y, tile))
        return FALSE;
    if (tile == 0 || tile == 1 || tile == 14)
        return FALSE;
    return TRUE;
}

void
handle_input_lobby(OUT game_t *game,
                   IN UINT8 keys)
{
    lobby_state_t *lobby = lobby_get_state();

    lobby->is_moving = FALSE;
    if (!lobby->rng_initialized && keys) {
        random_init(keys);
        lobby->rng_initialized = TRUE;
    }
    if (lobby->is_changing_map)
        return;
    if (keys & J_A)
        handle_a_input(game);
    if (keys & J_B)
        game_changer(game, GAME_STATE_MG2, TRUE);
    if (keys & J_SELECT)
        game_changer(game, GAME_STATE_MENU, TRUE);
    if (keys & J_LEFT && !is_colliding_with_wall(game, MOVING_SENS_LEFT)) {
        lobby->player_x -= SPEED;
        lobby->is_moving = TRUE;
        lobby->moving_dir = MOVING_SENS_LEFT;
    }
    if (keys & J_RIGHT && !is_colliding_with_wall(game, MOVING_SENS_RIGHT)) {
        lobby->player_x += SPEED;
        lobby->is_moving = TRUE;
        lobby->moving_dir = MOVING_SENS_RIGHT;
    }
    if (keys & J_UP && !is_colliding_with_wall(game, MOVING_SENS_UP)) {
        lobby->player_y -= SPEED;
        lobby->is_moving = TRUE;
        lobby->moving_dir = MOVING_SENS_UP;
    }
    if (keys & J_DOWN && !is_colliding_with_wall(game, MOVING_SENS_DOWN)) {
        lobby->player_y += SPEED;
        lobby->is_moving = TRUE;
        lobby->moving_dir = MOVING_SENS_DOWN;
    }
}
