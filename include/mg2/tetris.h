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
