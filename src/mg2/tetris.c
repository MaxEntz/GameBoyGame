/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris.c
*/

#include "mg2/mg2.h"

/**
 * @brief Array of text elements for the HUD
 * Each element contains the text to display and its position on the screen
 * The last element is a NULL text to indicate the end of the array
 */
static const text_render_t mg2_labels[] = {
    {"SCORE",   MG2_SCORE_LABEL_X, MG2_SCORE_LABEL_Y},
    {"000000",  MG2_SCORE_VAL_X,   MG2_SCORE_VAL_Y},
    {"LEVEL",   MG2_LEVEL_LABEL_X, MG2_LEVEL_LABEL_Y},
    {"0",      MG2_LEVEL_VAL_X,   MG2_LEVEL_VAL_Y},
    {"LINES",   MG2_LINES_LABEL_X, MG2_LINES_LABEL_Y},
    {"0",     MG2_LINES_VAL_X,   MG2_LINES_VAL_Y},
    {NULL,      0,                 0}
};

/**
 * @brief Draw the HUD elements on the screen
 * 
 * @return void
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
    set_bkg_data(0, TETRIS_TILE_COUNT, tetris_tiles);
    text_renderer_init();
    set_bkg_tiles(0, 0, 20, 18, tetris_bg_map);
    draw_hud();
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
