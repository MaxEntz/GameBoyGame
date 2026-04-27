/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_grid.c
*/

#include "mg2/tetris_grid.h"

UINT8 tetris_grid[TETRIS_GRID_H][TETRIS_GRID_W];

void
grid_init(void)
{
    UINT8 r;
    UINT8 c;

    for (r = 0; r < TETRIS_GRID_H; r++)
        for (c = 0; c < TETRIS_GRID_W; c++)
            tetris_grid[r][c] = 0;
}
