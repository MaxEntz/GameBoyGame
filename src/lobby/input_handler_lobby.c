/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** input_handler_lobby.c
*/

#include "lobby/lobby.h"
#include "lobby/lore_lobby.h"
#include "common/random.h"
#include "common/save.h"

/**
 * @brief Get the tile immediately in front of the player based on their facing direction
 */
static UINT8
get_faced_tile(IN const lobby_state_t *lobby)
{
    INT16 x = lobby->player_x - 8;
    INT16 y = lobby->player_y - 16;

    if (x < 0 || y < 0 || x >= 160 || y >= 144)
        return 0;
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
    return get_tile_by_map(lobby->current_map, x, y);
}

/**
 * @brief Check if the player is colliding with a wall in the given direction
 */
static BOOLEAN
is_colliding_with_wall(IN game_t *game, IN UINT8 sens)
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
    tile = get_tile_by_map(lobby->current_map, x, y);
    if (switch_map(game, x, y, tile))
        return FALSE;
    if (tile == 0 || tile == 1 || tile == 14)
        return FALSE;
    return TRUE;
}

/**
 * @brief Trigger NPC dialogue if the player is facing an interactable NPC
 */
static void
handle_a_input(IN game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();
    UINT8 tile = get_faced_tile(lobby);

    if (tile >= 23 && tile <= 26 && lobby->dialogue_index == LORE_LEFT_INTRO)
        lore_start_dialogue(game);
    if (tile >= 27 && tile <= 30 && lobby->dialogue_index == LORE_RIGHT_INTRO)
        lore_start_dialogue(game);
}

/**
 * @brief Apply directional movement if not colliding with a wall
 */
static void
handle_movement(INOUT game_t *game, INOUT lobby_state_t *lobby, IN UINT8 keys)
{
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

void
handle_input_lobby(OUT game_t *game, IN UINT8 keys)
{
    lobby_state_t *lobby = lobby_get_state();

    lobby->is_moving = FALSE;
    if (!lobby->rng_initialized && keys) {
        random_init(keys);
        lobby->rng_initialized = TRUE;
    }
    if (lobby->is_changing_map)
        return;
    if (lobby->dialogue_index < LORE_STEP_COUNT && dialogue_is_active(&lobby->dialogue))
        return dialogue_handle_input(&lobby->dialogue, keys);
    if (keys & J_A)
        handle_a_input(game);
    if (keys & J_START) {
        if (lobby->dialogue_index >= LORE_STEP_COUNT)
            save_reset(game);
        else
            save_write(game);
    }
    if (keys & J_SELECT)
        game_changer(game, GAME_STATE_MENU, TRUE);
    handle_movement(game, lobby, keys);
}
