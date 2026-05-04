/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris.h
*/

#ifndef TETRIS_H_
#define TETRIS_H_

#include "common/common.h"
#include "common/game_changer.h"
#include "common/text_renderer.h"
#include "mg2/asset_tetris.h"
#include "mg2/tetris_layout.h"
#include "mg2/tetris_piece.h"
#include "mg2/tetris_grid.h"
#include "mg2/tetris_hud.h"

/**
 * @brief Tetris game state structure
 * 
 * @param curr_piece current falling piece
 * @param delay_frame frame counter for automatic piece dropping
 * @param move_frame frame counter for horizontal movement delay
 * @param cleared_lines total number of cleared lines (for level progression)
 */
typedef struct tetris_s {
    piece_t      curr_piece;
    piece_type_t next_type;
    UINT8        delay_frame;
    UINT8        move_frame;
    UINT8        cleared_lines;
} tetris_t;

/**
 * @brief Load the tetris assets and handle the tetris state
 * We can see it like a creator in CPP
 * @param game Pointer to the game structure
 * @return void
 */
void
tetris(OUT game_t *game);

/**
 * @brief Handle the input in the tetris state
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_tetris(OUT game_t *game,
                   IN UINT8 keys);

/**
 * @brief Update the tetris state
 * @param game Pointer to the game structure
 * @return void
 */
void
update_tetris(OUT game_t *game);

#endif /* !TETRIS_H_ */
