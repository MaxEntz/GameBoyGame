/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_piece.c
*/

#include <gb/gb.h>
#include "mg2/tetris.h"
#include "mg2/tetris_piece.h"
#include "mg2/tetris_layout.h"
#include "mg2/tetris_grid.h"
#include "mg2/asset_tetris.h"

const UINT8 piece_shapes[PIECE_COUNT][4][4] = {
    {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}, /* I */
    {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}, /* O */
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, /* T */
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}, /* S */
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}}, /* Z */
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, /* J */
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}, /* L */
};

void
piece_draw(IN const piece_t *piece)
{
    UINT8 row;
    UINT8 col;
    UINT8 tile_id;

    tile_id = (UINT8)(piece->type + TETRIS_TILE_BLOCK_I);
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (piece_shapes[piece->type][row][col])
                set_bkg_tile_xy(piece->x + col + MG2_PLAYFIELD_X,
                                piece->y + row, tile_id);
        }
    }
}

void
piece_erase(IN const piece_t *piece)
{
    UINT8 row;
    UINT8 col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (piece_shapes[piece->type][row][col])
                set_bkg_tile_xy(piece->x + col + MG2_PLAYFIELD_X,
                                piece->y + row, TETRIS_TILE_EMPTY);
        }
    }
}

BOOLEAN
piece_can_move_down(IN const piece_t *piece)
{
    UINT8 row;
    UINT8 col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (piece_shapes[piece->type][row][col]) {
                if (piece->y + row + 1 >= TETRIS_GRID_H)
                    return FALSE;
                if (tetris_grid[piece->y + row + 1][piece->x + col] != 0)
                    return FALSE;
            }
        }
    }
    return TRUE;
}

BOOLEAN
piece_can_move_left(IN const piece_t *piece)
{
    UINT8 row;
    UINT8 col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (piece_shapes[piece->type][row][col]) {
                if (piece->x + col == 0)
                    return FALSE;
                if (tetris_grid[piece->y + row][piece->x + col - 1] != 0)
                    return FALSE;
            }
        }
    }
    return TRUE;
}

BOOLEAN
piece_can_move_right(IN const piece_t *piece)
{
    UINT8 row;
    UINT8 col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (piece_shapes[piece->type][row][col]) {
                if (piece->x + col + 1 >= TETRIS_GRID_W)
                    return FALSE;
                if (tetris_grid[piece->y + row][piece->x + col + 1] != 0)
                    return FALSE;
            }
        }
    }
    return TRUE;
}

void
piece_lock(IN const piece_t *piece)
{
    UINT8 row;
    UINT8 col;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (piece_shapes[piece->type][row][col])
                tetris_grid[piece->y + row][piece->x + col] =
                    (UINT8)(piece->type + TETRIS_TILE_BLOCK_I);
        }
    }
}
