/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** flappy.c
*/

#include "mg3/mg3.h"

static flappy_t fbird;

static void
draw_pipe(IN pipe_t *pipe)
{
    UINT8 tile_x = pipe->pipe_x / 8;
    UINT8 col;
    UINT8 row;
    UINT8 clear_col = (tile_x + MG3_PIPE_WIDTH) % 32;

    for (col = tile_x; col < tile_x + MG3_PIPE_WIDTH; col++) {
        UINT8 actual_col = col % 32;
        for (row = 0; row < 18; row++) {
            if (row < pipe->pipe_y || row >= pipe->pipe_y + MG3_PIPE_GAP)
                set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_PIPE);
            else
                set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_EMPTY);
        }
    }
    for (row = 0; row < 18; row++)
        set_bkg_tile_xy(clear_col, row, FLAPPY_TILE_EMPTY);
}

void
flappybird(OUT game_t *game)
{
    (void)game;

    fbird.bird_y = MG3_SCREEN_Y / 2;
    for(UINT8 i = 0; i < MG3_NB_PIPE; i++){
        fbird.pipes[i].pipe_x = MG3_SCREEN_X + (i * 80);
        fbird.pipes[i].pipe_y = 9;
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
    move_sprite(0, MG3_BIRD_X, fbird.bird_y);
    fbird.bird_y += 1;

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
