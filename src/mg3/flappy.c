/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** flappy.c
*/

#include "mg3/mg3.h"

static flappy_t fbird;

static void
draw_color_pipe(IN pipe_t *pipe, UINT8 actual_col)
{
    for (UINT8 row = 0; row < 18; row++) {
        if (row < pipe->pipe_y || row >= pipe->pipe_y + MG3_PIPE_GAP)
            set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_PIPE);
        else
            set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_EMPTY);
    }
}

static UINT8
next_pipe_y(void)
{
    static UINT8 seed = 3;

    seed = (UINT8)((seed * 5 + 7) % 13);
    return (UINT8)(MG3_PIPE_Y_MIN + seed % (MG3_PIPE_Y_MAX - MG3_PIPE_Y_MIN + 1));
}

static void
draw_pipe(IN pipe_t *pipe)
{
    INT16 tile_x_raw = pipe->pipe_x / 8;
    UINT8 col;
    UINT8 actual_col;
    UINT8 clear_col;

    clear_col = (UINT8)((tile_x_raw + MG3_PIPE_WIDTH) % 32);
    for (UINT8 row = 0; row < 18; row++)
        set_bkg_tile_xy(clear_col, row, FLAPPY_TILE_EMPTY);

    if (pipe->pipe_x <= 0) {
        for (col = 0; col < MG3_PIPE_WIDTH; col++) {
            actual_col = (UINT8)((tile_x_raw + col) % 32);
            for (UINT8 row = 0; row < 12; row++)
                set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_EMPTY);
        }
        return;
    }

    for (col = 0; col < MG3_PIPE_WIDTH; col++) {
        actual_col = (UINT8)((tile_x_raw + col) % 32);
        draw_color_pipe(pipe, actual_col);
    }
}

void
flappybird(OUT game_t *game)
{
    (void)game;

    fbird.bird_y = MG3_SCREEN_Y / 2;
    for(UINT8 i = 0; i < MG3_NB_PIPE; i++){
        fbird.pipes[i].pipe_x = MG3_SCREEN_X + (i * MG3_PIPE_SPACING);
        fbird.pipes[i].pipe_y = next_pipe_y();
    }

    set_bkg_data(0, FLAPPY_TILE_COUNT, flappy_tiles);
    set_bkg_tiles(0, 0, 20, 18, flappy_bg_map);
    set_sprite_data(0, 1, &flappy_tiles[FLAPPY_TILE_BIRD * 16]);
    set_sprite_tile(0, 0);
}

void
update_flappybird(OUT game_t *game)
{
    (void)game;

    fbird.bird_y += 1;

    if (fbird.bird_y < 16)
        fbird.bird_y = 16;
    if (fbird.bird_y > MG3_SCREEN_Y + 16)
        fbird.bird_y = MG3_SCREEN_Y + 16;
    move_sprite(0, MG3_BIRD_X, (UINT8)fbird.bird_y);
    for (UINT8 i = 0; i < MG3_NB_PIPE; i++){
        fbird.pipes[i].pipe_x -= 1;
        draw_pipe(&fbird.pipes[i]);
        if (fbird.pipes[i].pipe_x <= 0)
            fbird.pipes[i].pipe_x = MG3_SCREEN_X;
    }
}

void
handle_input_flappybird(OUT game_t *game, 
                        IN UINT8 keys)
{
    (void)game;
    if (keys & J_A)
        fbird.bird_y -= MG3_JUMP;
}
