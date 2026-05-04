/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** map_manager_lobby.c
*/

#include "lobby/lobby.h"

static const map_manager_t g_map_manager[11] = {
    {MAP_ID_INVALID, NULL}, /* 0 */
    {MAP_ID_TL, map_tl},
    {MAP_ID_TC, map_tc},
    {MAP_ID_TR, map_tr},
    {MAP_ID_CL, map_cl},
    {MAP_ID_CC, map_cc},
    {MAP_ID_CR, map_cr},
    {MAP_ID_BL, map_bl},
    {MAP_ID_BC, map_bc},
    {MAP_ID_BR, map_br},
    {MAP_ID_INVALID, NULL} /* 10 */
};

/**
 * @brief Swap the current map with a new map
 * @param game Pointer to the game structure
 * @param new_map_id The ID of the new map
 * @param dir The direction of the transition
 * @return TRUE if the map was swapped, FALSE otherwise
 */
static BOOLEAN
swap_map_with_param(game_t *game, map_id_t new_map_id, transition_dir_t dir)
{
    if (new_map_id < MAP_ID_TL || new_map_id > MAP_ID_BR)
        return FALSE;
    game->current_map_id = new_map_id;
    game->is_changing_map = TRUE;
    for (UINT16 i = 0; i < 20 * 18; i++)
        game->current_map[i] = g_map_manager[game->current_map_id].map_data[i];
    transition_map_animation(game, dir);
    return TRUE;
}

BOOLEAN
switch_map(game_t *game,
           INT16 x,
           INT16 y,
           UINT8 tile)
{
    if ((x != 0 && y != 0) && (x != 160 - 16 && y != 144 - 16))
        return FALSE;
    if (tile != 14)
        return FALSE;
    if (y == 0 && game->moving_dir == MOVING_SENS_UP) {
        return swap_map_with_param(game, game->current_map_id + MAP_UP, TRANSITION_TB);
    } else if (y >= 144 - 16 && game->moving_dir == MOVING_SENS_DOWN) {
        return swap_map_with_param(game, game->current_map_id + MAP_DOWN, TRANSITION_BT);
    } else if (x == 0 && game->moving_dir == MOVING_SENS_LEFT) {
        return swap_map_with_param(game, game->current_map_id + MAP_LEFT, TRANSITION_LR);
    } else if (x == 160 - 16 && game->moving_dir == MOVING_SENS_RIGHT) {
        return swap_map_with_param(game, game->current_map_id + MAP_RIGHT, TRANSITION_RL);
    }
    return FALSE;
}
