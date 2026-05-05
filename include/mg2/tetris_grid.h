/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_grid.h
*/

#ifndef TETRIS_GRID_H_
    #define TETRIS_GRID_H_

    #include "common/project_types.h"

    #define TETRIS_GRID_W  10
    #define TETRIS_GRID_H  18

extern UINT8 tetris_grid[TETRIS_GRID_H][TETRIS_GRID_W];

/**
 * @brief init the tetris grid with empty values
 */
void
grid_init(void);

/**
 * @brief Detect and remove full rows
 * @return Number of lines cleared (0-4)
 */
UINT8
grid_clear_lines(void);

/**
 * @brief Redraw the entire playfield from grid data
 * 
 * PAS OPTI
 */
void
grid_draw_playfield(void);

#endif /* !TETRIS_GRID_H_ */
