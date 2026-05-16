/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** flappy.c
*/

#include "mg3/mg3.h"

static flappy_t fbird;

/**
 * @brief Draw a single column of a pipe on the background
 *
 * @param pipe pointer to the pipe to draw
 * @param actual_col background column index to draw on (0-31)
 */

static void
draw_color_pipe(IN pipe_t *pipe,
                IN UINT8 actual_col)
{
    for (UINT8 row = 2; row < COMMON_SCREEN_HEIGHT_TILES; row++) {
        if (row < pipe->pipe_y || row >= pipe->pipe_y + fbird.pipe_gap)
            set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_PIPE);
        else
            set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_EMPTY);
    }
}

/**
 * @brief Generate a pseudo-random vertical position for the pipe gap
 *
 * @return gap position between MG3_PIPE_Y_MIN and MG3_PIPE_Y_MAX
 */
static UINT8
next_pipe_y(void)
{
    return MG3_PIPE_Y_MIN + random_get(MG3_PIPE_Y_MAX - MG3_PIPE_Y_MIN + 1);
}

/**
 * @brief Draw a pipe on the background or erase it if out of screen
 *
 * @param pipe pointer to the pipe to draw
 */
static void
draw_pipe(IN pipe_t *pipe)
{
    INT16 tile_x = pipe->pipe_x / MG3_PX_TO_TILE;
    UINT8 actual_col = 0;
    UINT8 col = 0;
    UINT8 clear_col = (tile_x + MG3_PIPE_WIDTH) & (MG3_BKG_WIDTH_SIZE - 1);

    for (UINT8 row = 2; row < COMMON_SCREEN_HEIGHT_TILES; row++)
        set_bkg_tile_xy(clear_col, row, FLAPPY_TILE_EMPTY);
    if (pipe->pipe_x <= 0) {
        for (col = 0; col < MG3_PIPE_WIDTH; col++) {
            actual_col = (tile_x + col) & (MG3_BKG_WIDTH_SIZE - 1);
            for (UINT8 row = 2; row < COMMON_SCREEN_HEIGHT_TILES; row++)
                set_bkg_tile_xy(actual_col, row, FLAPPY_TILE_EMPTY);
        }
        return;
    }
    for (col = 0; col < MG3_PIPE_WIDTH; col++) {
        actual_col = (tile_x + col) & (MG3_BKG_WIDTH_SIZE - 1);
        draw_color_pipe(pipe, actual_col);
    }
}

/**
 * @brief Check if the bird collides with any pipe
 *
 * @return TRUE if a collision is detected, FALSE otherwise
 */
static BOOLEAN
check_collision(void)
{
    UINT8 bird_tile_x  = MG3_BIRD_X / MG3_PX_TO_TILE;
    UINT8 bird_tile_y1 = (fbird.bird_y - MG3_SPRITE_Y_OFFSET) / MG3_PX_TO_TILE;
    UINT8 bird_tile_y2 = bird_tile_y1 + 1;
    UINT8 tile_x = 0;

    for (UINT8 i = 0; i < MG3_NB_PIPE; i++) {
        tile_x = fbird.pipes[i].pipe_x / MG3_PX_TO_TILE;
        if (bird_tile_x < tile_x || bird_tile_x >= tile_x + MG3_PIPE_WIDTH)
            continue;
        if (bird_tile_y1 < fbird.pipes[i].pipe_y ||
            bird_tile_y2 >= fbird.pipes[i].pipe_y + fbird.pipe_gap)
            return TRUE;
    }
    return FALSE;
}

/**
 * @brief Convert an unsigned integer to a fixed-width decimal string
 *
 * @param val value to convert
 * @param buf destination buffer (must be at least width + 1 bytes)
 * @param width number of digits to write
 */
static void
uint_to_str(IN UINT16 val,
            OUT CHAR *buf,
            IN UINT8 width)
{
    for (INT8 i = (INT8)(width - 1); i >= 0; i--) {
        buf[i] = '0' + (CHAR)(val % 10);
        val /= 10;
    }
    buf[width] = '\0';
}

/**
 * @brief Draw the current score on the top-left of the screen
 */
static void
draw_score(void)
{
    CHAR buf[4];
    text_render_t render;

    render.text = buf;
    render.x = 1;
    render.y = 1;

    if (fbird.pipes_passed != fbird.last_score) {
        uint_to_str(fbird.pipes_passed, buf, 3);
        text_renderer_draw(&render);
        fbird.last_score = fbird.pipes_passed;
    }
}

/**
 * @brief Move all pipes, update score and difficulty scaling
 *
 * @param game pointer to the game structure
 */
static void
update_pipes(OUT game_t *game)
{
    for (UINT8 i = 0; i < MG3_NB_PIPE; i++) {
        fbird.pipes[i].pipe_x -= fbird.pipe_speed;
        draw_pipe(&fbird.pipes[i]);
        if (fbird.pipes[i].pipe_x < MG3_BIRD_X &&
            fbird.pipes[i].pipe_x + fbird.pipe_speed >= MG3_BIRD_X) {
            fbird.pipes_passed++;
            game->score_mg3 = fbird.pipes_passed;
            if (fbird.pipes_passed % MG3_PIPE_SPEED_STEP == 0) {
                if (fbird.pipe_speed < MG3_PIPE_SPEED_MAX) {
                    fbird.pipe_speed++;
                    fbird.jump_force++;
                    if (fbird.pipe_gap < MG3_PIPE_GAP + 2)
                        fbird.pipe_gap++;
                }
            }
        }
        if (fbird.pipes[i].pipe_x <= 0) {
            fbird.pipes[i].pipe_x = MG3_SCREEN_X_PX;
            fbird.pipes[i].pipe_y = next_pipe_y();
        }
    }
}

void
flappybird(OUT game_t *game)
{
    (void)game;
    fbird.last_score = 0;
    fbird.bird_y = MG3_SCREEN_Y_PX / 2;
    fbird.pipes_passed = 0;
    fbird.pipe_speed = MG3_PIPE_SPEED_INIT;
    fbird.jump_force = MG3_JUMP_INIT;
    fbird.pipe_gap = MG3_PIPE_GAP;

    for(UINT8 i = 0; i < MG3_NB_PIPE; i++){
        fbird.pipes[i].pipe_x = MG3_SCREEN_X_PX + (i * MG3_PIPE_SPACING);
        fbird.pipes[i].pipe_y = next_pipe_y();
    }
    set_bkg_data(0, FLAPPY_TILE_COUNT, flappy_tiles);
    set_bkg_tiles(0, 0, COMMON_SCREEN_WIDTH_TILES, COMMON_SCREEN_HEIGHT_TILES, flappy_bg_map);
    set_sprite_data(0, 1, &flappy_tiles[FLAPPY_TILE_BIRD * MG3_SPRITE_Y_OFFSET]);
    set_sprite_tile(0, 0);
    text_renderer_init();
}

void
update_flappybird(OUT game_t *game)
{
    draw_score();
    if (check_collision() || fbird.bird_y >= MG3_SCREEN_Y_PX + MG3_SPRITE_Y_OFFSET) {
        game_changer(game, GAME_STATE_LOBBY, TRUE);
        return;
    }
    fbird.bird_y += 1;
    move_sprite(0, MG3_BIRD_X, fbird.bird_y);
    update_pipes(game);
}

void
handle_input_flappybird(OUT game_t *game,
                        IN UINT8 keys)
{
    (void)game;
    if (keys & J_A) {
        fbird.bird_y -= fbird.jump_force;
        if (fbird.bird_y < MG3_SPRITE_Y_OFFSET)
            fbird.bird_y = MG3_SPRITE_Y_OFFSET;
    }
}
