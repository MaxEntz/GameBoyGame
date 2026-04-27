/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris.c
*/

#include "mg2/tetris.h"

static piece_t g_piece;

static const text_render_t mg2_labels[] = {
    {"SCORE",   MG2_SCORE_LABEL_X, MG2_SCORE_LABEL_Y},
    {"000000",  MG2_SCORE_VAL_X,   MG2_SCORE_VAL_Y},
    {"LEVEL",   MG2_LEVEL_LABEL_X, MG2_LEVEL_LABEL_Y},
    {"0",       MG2_LEVEL_VAL_X,   MG2_LEVEL_VAL_Y},
    {"LINES",   MG2_LINES_LABEL_X, MG2_LINES_LABEL_Y},
    {"0",       MG2_LINES_VAL_X,   MG2_LINES_VAL_Y},
    {NULL,      0,                 0}
};

/**
 * @brief Draw all HUD labels on the background
 */
static void
draw_hud(void)
{
    UINT8 i = 0;

    while (mg2_labels[i].text != NULL)
        text_renderer_draw(&mg2_labels[i++]);
}

void
tetris(OUT game_t *game)
{
    (void)game;
    grid_init();
    g_piece.type = PIECE_I;
    g_piece.x = PIECE_SPAWN_X;
    g_piece.y = PIECE_SPAWN_Y;
    move_sprite(0, 0, 0);
    set_bkg_data(0, TETRIS_TILE_COUNT, tetris_tiles);
    text_renderer_init();
    set_bkg_tiles(0, 0, 20, 18, tetris_bg_map);
    draw_hud();
    piece_draw(&g_piece);
    SHOW_BKG;
    DISPLAY_ON;
}

void
update_tetris(OUT game_t *game)
{
    (void)game;
}

void
handle_input_tetris(OUT game_t *game,
                   IN UINT8 keys)
{
    (void)game;
    (void)keys;
}
