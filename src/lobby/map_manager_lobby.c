/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** map_manager_lobby.c
*/

#include "lobby/lobby.h"

const map_manager_t g_map_manager[11] = {
    {NULL, NULL}, /* 0 */
    {MAP_TL, map_tl},
    {MAP_TC, map_tc},
    {MAP_TR, map_tr},
    {MAP_CL, map_cl},
    {MAP_CC, map_cc},
    {MAP_CR, map_cr},
    {MAP_BL, map_bl},
    {MAP_BC, map_bc},
    {MAP_BR, map_br},
    {NULL, NULL} /* 10 */
};

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
        game->current_map_id = game->current_map_id + MAP_UP;
        game->is_changing_map = TRUE;
        for (UINT16 i = 0; i < 20 * 18; i++)
            game->current_map[i] = g_map_manager[game->current_map_id].map_data[i];
        transition_map_animation(game, TRANSITION_TB);
        return TRUE;
    } else if (y >= 144 - 16 && game->moving_dir == MOVING_SENS_DOWN) {
        game->current_map_id = game->current_map_id + MAP_DOWN;
        game->is_changing_map = TRUE;
        for (UINT16 i = 0; i < 20 * 18; i++)
            game->current_map[i] = g_map_manager[game->current_map_id].map_data[i];
        transition_map_animation(game, TRANSITION_BT);
        return TRUE;
    } else if (x == 0 && game->moving_dir == MOVING_SENS_LEFT) {
        game->current_map_id = game->current_map_id + MAP_LEFT;
        game->is_changing_map = TRUE;
        for (UINT16 i = 0; i < 20 * 18; i++)
            game->current_map[i] = g_map_manager[game->current_map_id].map_data[i];
        transition_map_animation(game, TRANSITION_LR);
        return TRUE;
    } else if (x == 160 - 16 && game->moving_dir == MOVING_SENS_RIGHT) {
        game->current_map_id = game->current_map_id + MAP_RIGHT;
        game->is_changing_map = TRUE;
        for (UINT16 i = 0; i < 20 * 18; i++)
            game->current_map[i] = g_map_manager[game->current_map_id].map_data[i];
        transition_map_animation(game, TRANSITION_RL);
        return TRUE;
    }
    return FALSE;
}
