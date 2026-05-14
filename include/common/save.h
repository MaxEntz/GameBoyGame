/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** save.h
*/

#ifndef SAVE_H_
    #define SAVE_H_

    #include "common/common.h"

    #define SAVE_MAGIC 0x1A71U

/**
 * @brief Battery-backed SRAM layout stored at 0xA000
 *
 * magic must equal SAVE_MAGIC; any other value means
 * the cartridge is fresh or the save is corrupt.
 * best_mg* tracks the all-time high score for each mini-game.
 * run_mg*  stores the score locked in after defeating each boss
 * in the current (or last completed) run.
 */
typedef struct save_data_s {
    UINT16   magic;
    UINT16   best_mg1;
    UINT16   best_mg2;
    UINT16   best_mg3;
    UINT16   run_mg1;
    UINT16   run_mg2;
    UINT16   run_mg3;
    UINT8    dialogue_index;
    UINT8    player_x;
    UINT8    player_y;
    UINT8    current_map_id;
} save_data_t;

#endif /* !SAVE_H_ */
