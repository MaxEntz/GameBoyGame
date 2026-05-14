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
    #define SRAM_BASE  ((UINT8 *)0xA000U)

/**
 * @brief structure to hold the save data for the game
 *
 * magic must equal SAVE_MAGIC
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

/**
 * @brief Load the save data from SRAM and update the game and lobby state
 * 
 * @param game Pointer to the game structure to update with the loaded save data
 */
void save_load(INOUT game_t *game);

/**
 * @brief Write the current game and lobby state to SRAM as save data
 * 
 * @param game Pointer to the game structure containing the data to save
 */
void save_write(INOUT game_t *game);

/**
 * @brief Reset the save data in SRAM by clearing the magic value
 */
void save_reset(IN const game_t *game);

#endif /* !SAVE_H_ */
