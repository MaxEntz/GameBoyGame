/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** save.c
*/

#include <string.h>
#include "common/save.h"
#include "lobby/lobby.h"

void
save_load(INOUT game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();
    save_data_t tmp;

    ENABLE_RAM;
    memcpy(&tmp, (const void *)SRAM_BASE, sizeof(save_data_t));
    DISABLE_RAM;
    if (tmp.magic != SAVE_MAGIC)
        return;
    game->best_score_mg1 = tmp.best_mg1;
    game->best_score_mg2 = tmp.best_mg2;
    game->best_score_mg3 = tmp.best_mg3;
    game->score_mg1 = tmp.run_mg1;
    game->score_mg2 = tmp.run_mg2;
    game->score_mg3 = tmp.run_mg3;
    lobby->player_x = tmp.player_x;
    lobby->player_y = tmp.player_y;
    lobby->dialogue_index = tmp.dialogue_index;
    set_map(lobby, (map_id_t)tmp.current_map_id);
}

void
save_write(IN const game_t *game)
{
    const lobby_state_t *lobby = lobby_get_state();
    save_data_t tmp;

    tmp.best_mg1 = game->best_score_mg1;
    tmp.best_mg2 = game->best_score_mg2;
    tmp.best_mg3 = game->best_score_mg3;
    tmp.run_mg1 = game->score_mg1;
    tmp.run_mg2 = game->score_mg2;
    tmp.run_mg3 = game->score_mg3;
    tmp.dialogue_index = lobby->dialogue_index;
    tmp.player_x = lobby->player_x;
    tmp.player_y = lobby->player_y;
    tmp.current_map_id = (UINT8)lobby->current_map_id;
    tmp.magic = SAVE_MAGIC;
    ENABLE_RAM;
    memcpy((void *)SRAM_BASE, &tmp, sizeof(save_data_t));
    DISABLE_RAM;
}
