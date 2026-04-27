/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_piece.c
*/

#include <gb/gb.h>
#include "mg2/tetris_piece.h"
#include "mg2/tetris_layout.h"
#include "mg2/asset_tetris.h"

// 4x4, 1byte = 1 row
const UINT8 piece_shapes[PIECE_COUNT][4] = {
    {0x0F, 0x00, 0x00, 0x00}, /* I */
    {0x06, 0x06, 0x00, 0x00}, /* O */
    {0x02, 0x07, 0x00, 0x00}, /* T */
    {0x06, 0x03, 0x00, 0x00}, /* S */
    {0x03, 0x06, 0x00, 0x00}, /* Z */
    {0x01, 0x07, 0x00, 0x00}, /* J */
    {0x04, 0x07, 0x00, 0x00}, /* L */
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
            if (piece_shapes[piece->type][row] & (1 << col))
                set_bkg_tile_xy(piece->x + col + MG2_PLAYFIELD_X, piece->y + row, tile_id);
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
            if (piece_shapes[piece->type][row] & (1 << col))
                set_bkg_tile_xy(piece->x + col + MG2_PLAYFIELD_X, piece->y + row, TETRIS_TILE_EMPTY);
        }
    }
}
