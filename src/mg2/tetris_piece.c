/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_piece.c
*/

#include <gb/gb.h>
#include "mg2/tetris_piece.h"
#include "mg2/tetris_layout.h"
#include "mg2/tetris_grid.h"
#include "mg2/asset_tetris.h"

const UINT8 piece_shapes[PIECE_COUNT][4][4][4] = {
    /* PIECE_I */
    {
        {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}},
        {{1,1,1,1}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}},
    },
    /* PIECE_O */
    {
        {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    },
    /* PIECE_T */
    {
        {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,0,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}},
        {{1,1,1,0}, {0,1,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}},
    },
    /* PIECE_S */
    {
        {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}},
        {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}},
    },
    /* PIECE_Z */
    {
        {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}},
        {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}},
    },
    /* PIECE_J */
    {
        {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,1,0,0}, {1,0,0,0}, {1,0,0,0}, {0,0,0,0}},
        {{1,1,1,0}, {0,0,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {0,0,0,0}},
    },
    /* PIECE_L */
    {
        {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,0,0,0}, {1,0,0,0}, {1,1,0,0}, {0,0,0,0}},
        {{1,1,1,0}, {1,0,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0}},
    },
};

static BOOLEAN
piece_fits(IN const piece_t *piece, IN UINT8 new_rot, IN INT8 gap)
{
    UINT8 row;
    UINT8 col;
    INT8  tx;
    UINT8 ty;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (piece_shapes[piece->type][new_rot][row][col]) {
                tx = (INT8)(piece->x + gap + (INT8)col);
                ty = piece->y + row;
                if (tx < 0 || tx >= TETRIS_GRID_W)
                    return FALSE;
                if (ty >= TETRIS_GRID_H)
                    return FALSE;
                if (tetris_grid[ty][(UINT8)tx] != 0)
                    return FALSE;
            }
        }
    }
    return TRUE;
}

void
piece_draw(IN const piece_t *piece)
{
    UINT8 row;
    UINT8 col;
    UINT8 tile_id;

    tile_id = (UINT8)(piece->type + TETRIS_TILE_BLOCK_I);
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (piece_shapes[piece->type][piece->rot][row][col])
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
            if (piece_shapes[piece->type][piece->rot][row][col])
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
            if (piece_shapes[piece->type][piece->rot][row][col]) {
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
            if (piece_shapes[piece->type][piece->rot][row][col]) {
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
            if (piece_shapes[piece->type][piece->rot][row][col]) {
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
            if (piece_shapes[piece->type][piece->rot][row][col])
                tetris_grid[piece->y + row][piece->x + col] =
                    (UINT8)(piece->type + TETRIS_TILE_BLOCK_I);
        }
    }
}

void
rotate_r(INOUT piece_t *piece)
{
    UINT8 new_rot = (piece->rot + 1) % 4;
    INT8  gap;

    if (piece_fits(piece, new_rot, 0))
        gap = 0;
    else if (piece_fits(piece, new_rot, -1))
        gap = -1;
    else if (piece_fits(piece, new_rot, 1))
        gap = 1;
    else
        return;
    piece_erase(piece);
    piece->rot = new_rot;
    piece->x = (INT8)(piece->x + gap);
    piece_draw(piece);
}

void
rotate_l(INOUT piece_t *piece)
{
    UINT8 new_rot = (piece->rot + 3) % 4;
    INT8  gap;

    if (piece_fits(piece, new_rot, 0))
        gap = 0;
    else if (piece_fits(piece, new_rot, -1))
        gap = -1;
    else if (piece_fits(piece, new_rot, 1))
        gap = 1;
    else
        return;
    piece_erase(piece);
    piece->rot = new_rot;
    piece->x = (INT8)(piece->x + gap);
    piece_draw(piece);
}
