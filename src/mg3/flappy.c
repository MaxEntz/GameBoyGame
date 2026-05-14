/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** flappy.c
*/

#include "mg3/mg3.h"

static flappy_t fbird;

static void
draw_color_pipe(IN pipe_t *pipe, IN UINT8 actual_col)
{
    for (UINT8 row = 0; row < COMMON_SCREEN_HEIGHT_TILES; row++) {
        if (row < pipe->pipe_y || row >= pipe->pipe_y + MG3_PIPE_GAP)
            set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_PIPE);
        else
            set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_EMPTY);
    }
}

static UINT8
next_pipe_y(void)
{
    return (UINT8)(MG3_PIPE_Y_MIN + random_get(MG3_PIPE_Y_MAX - MG3_PIPE_Y_MIN + 1));
}

static void
draw_pipe(IN pipe_t *pipe)
{
    INT16 tile_x_raw = pipe->pipe_x / 8;
    UINT8 col = 0;
    UINT8 actual_col = 0;
    UINT8 clear_col = 0;

    clear_col = (UINT8)((tile_x_raw + MG3_PIPE_WIDTH) % MG3_BKG_WIDTH_SIZE);
    for (UINT8 row = 0; row < COMMON_SCREEN_HEIGHT_TILES; row++)
        set_bkg_tile_xy(clear_col, row, FLAPPY_TILE_EMPTY);

    if (pipe->pipe_x <= 0) {
        for (col = 0; col < MG3_PIPE_WIDTH; col++) {
            actual_col = (UINT8)((tile_x_raw + col) % MG3_BKG_WIDTH_SIZE);
            for (UINT8 row = 0; row < COMMON_SCREEN_HEIGHT_TILES; row++)
                set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_EMPTY);
        }
        return;
    }

    for (col = 0; col < MG3_PIPE_WIDTH; col++) {
        actual_col = (UINT8)((tile_x_raw + col) % MG3_BKG_WIDTH_SIZE);
        draw_color_pipe(pipe, actual_col);
    }
}

static BOOLEAN
check_collision(void)
{
    UINT8 bird_tile_x  = MG3_BIRD_X / 8;
    UINT8 bird_tile_y1 = (UINT8)((fbird.bird_y - MG3_SPRITE_Y_OFFSET) / 8);
    UINT8 bird_tile_y2 = bird_tile_y1 + 1;
    UINT8 tile_x = 0;

    for (UINT8 i = 0; i < MG3_NB_PIPE; i++) {
        tile_x = (UINT8)(fbird.pipes[i].pipe_x / 8);
        if (bird_tile_x < tile_x || bird_tile_x >= tile_x + MG3_PIPE_WIDTH)
            continue;
        if (bird_tile_y1 < fbird.pipes[i].pipe_y ||
            bird_tile_y2 >= fbird.pipes[i].pipe_y + MG3_PIPE_GAP)
            return TRUE;
    }
    return FALSE;
}

void
flappybird(OUT game_t *game)
{
    (void)game;

    fbird.bird_y = MG3_SCREEN_Y_PX / 2;
    for(UINT8 i = 0; i < MG3_NB_PIPE; i++){
        fbird.pipes[i].pipe_x = MG3_SCREEN_X_PX + (i * MG3_PIPE_SPACING);
        fbird.pipes[i].pipe_y = next_pipe_y();
    }

    set_bkg_data(0, FLAPPY_TILE_COUNT, flappy_tiles);
    set_bkg_tiles(0, 0, COMMON_SCREEN_WIDTH_TILES, COMMON_SCREEN_HEIGHT_TILES, flappy_bg_map);
    set_sprite_data(0, 1, &flappy_tiles[FLAPPY_TILE_BIRD * MG3_SPRITE_Y_OFFSET]);
    set_sprite_tile(0, 0);
}

void
update_flappybird(OUT game_t *game)
{
    if (check_collision() || fbird.bird_y >= MG3_SCREEN_Y_PX + MG3_SPRITE_Y_OFFSET) {
        game_changer(game, GAME_STATE_LOBBY, TRUE);
        return;
    }

    fbird.bird_y += 1;

    if (fbird.bird_y < MG3_SPRITE_Y_OFFSET)
        fbird.bird_y = MG3_SPRITE_Y_OFFSET;
    if (fbird.bird_y > MG3_SCREEN_Y_PX + MG3_SPRITE_Y_OFFSET)
        fbird.bird_y = MG3_SCREEN_Y_PX + MG3_SPRITE_Y_OFFSET;
    move_sprite(0, MG3_BIRD_X, (UINT8)fbird.bird_y);
    for (UINT8 i = 0; i < MG3_NB_PIPE; i++){
        fbird.pipes[i].pipe_x -= 1;
        draw_pipe(&fbird.pipes[i]);
        if (fbird.pipes[i].pipe_x <= 0){
            fbird.pipes[i].pipe_x = MG3_SCREEN_X_PX;
            fbird.pipes[i].pipe_y = next_pipe_y();
        }
    }
}

void
handle_input_flappybird(OUT game_t *game, 
                        IN UINT8 keys)
{
    (void)game;
    if (keys & J_A){
        fbird.bird_y -= MG3_JUMP;
    }
}
