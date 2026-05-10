/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_hud.c
*/

#include <gb/gb.h>
#include "common/text_renderer.h"
#include "mg2/tetris_hud.h"
#include "mg2/tetris_layout.h"
#include "mg2/tetris_piece.h"
#include "mg2/asset_tetris.h"

static const text_render_t mg2_labels[] = {
    {"SCORE", MG2_SCORE_LABEL_X, MG2_SCORE_LABEL_Y},
    {"LEVEL", MG2_LEVEL_LABEL_X, MG2_LEVEL_LABEL_Y},
    {"LINES", MG2_LINES_LABEL_X, MG2_LINES_LABEL_Y},
    {NULL,    0,                 0}
};

/**
 * @brief Write val as a zero-padded decimal string of exactly width digits
 */
static void
uint_to_str(UINT16 val, CHAR *buf, UINT8 width)
{
    INT8 i;

    for (i = (INT8)(width - 1); i >= 0; i--) {
        buf[i] = '0' + (CHAR)(val % 10);
        val /= 10;
    }
    buf[width] = '\0';
}

void
draw_score(INT16 score)
{
    CHAR          buf[7];
    text_render_t render = {buf, MG2_SCORE_VAL_X, MG2_SCORE_VAL_Y};

    uint_to_str((UINT16)score, buf, 6);
    text_renderer_draw(&render);
}

void
draw_lines(UINT8 lines)
{
    CHAR          buf[4];
    text_render_t render = {buf, MG2_LINES_VAL_X, MG2_LINES_VAL_Y};

    uint_to_str((UINT16)lines, buf, 3);
    text_renderer_draw(&render);
}

void
draw_level(UINT8 level)
{
    CHAR          buf[3];
    text_render_t render = {buf, MG2_LEVEL_VAL_X, MG2_LEVEL_VAL_Y};

    uint_to_str((UINT16)level, buf, 2);
    text_renderer_draw(&render);
}

void
draw_hud(INT16 score, UINT8 level, UINT8 lines)
{
    UINT8 i = 0;

    while (mg2_labels[i].text != NULL)
        text_renderer_draw(&mg2_labels[i++]);
    draw_score(score);
    draw_level(level);
    draw_lines(lines);
}

void
draw_next_piece(piece_type_t type)
{
    UINT8 row;
    UINT8 col;

    for (row = 0; row < 3; row++)
        for (col = 0; col < 4; col++)
            set_bkg_tile_xy((UINT8)(MG2_NEXT_INNER_X + col),
                            (UINT8)(MG2_NEXT_INNER_Y + row),
                            piece_shapes[type][0][row][col]
                                ? (UINT8)(type + TETRIS_TILE_BLOCK_I)
                                : TETRIS_TILE_EMPTY);
}
