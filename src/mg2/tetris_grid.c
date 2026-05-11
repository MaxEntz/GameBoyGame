/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_grid.c
*/

#include <gb/gb.h>
#include "mg2/tetris_grid.h"
#include "mg2/tetris_layout.h"
#include "mg2/asset_tetris.h"

UINT8 tetris_grid[TETRIS_GRID_H][TETRIS_GRID_W];

/**
 * @brief Check if a grid row is full
 * 
 * @param r row index to check
 * @return TRUE if the row is full, FALSE otherwise
 */
static BOOLEAN
row_is_full(UINT8 r)
{
    UINT8 c;

    for (c = 0; c < TETRIS_GRID_W; c++)
        if (tetris_grid[r][c] == 0)
            return FALSE;
    return TRUE;
}

/**
 * @brief Remove row r and shift everything above it down by one
 */
static void
row_collapse(UINT8 r)
{
    UINT8 i;
    UINT8 c;

    for (i = r; i > 0; i--)
        for (c = 0; c < TETRIS_GRID_W; c++)
            tetris_grid[i][c] = tetris_grid[i - 1][c];
    for (c = 0; c < TETRIS_GRID_W; c++)
        tetris_grid[0][c] = 0;
}

void
grid_init(void)
{
    UINT8 r;
    UINT8 c;

    for (r = 0; r < TETRIS_GRID_H; r++)
        for (c = 0; c < TETRIS_GRID_W; c++)
            tetris_grid[r][c] = 0;
}

UINT8
grid_clear_lines(void)
{
    UINT8 r = 0;
    UINT8 cleared = 0;

    while (r < TETRIS_GRID_H) {
        if (row_is_full(r)) {
            row_collapse(r);
            cleared++;
        } else {
            r++;
        }
    }
    return cleared;
}

void
grid_draw_playfield(void)
{
    UINT8 r;
    UINT8 c;
    UINT8 tile;

    for (r = 0; r < TETRIS_GRID_H; r++) {
        for (c = 0; c < TETRIS_GRID_W; c++) {
            tile = (tetris_grid[r][c] != 0) ? tetris_grid[r][c] : TETRIS_TILE_EMPTY;
            set_bkg_tile_xy((UINT8)(c + MG2_PLAYFIELD_X), r, tile);
        }
    }
}
