/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** flappy.c
*/

#include "mg3/mg3.h"

static flappy_t fbird;

/**
 * @brief Move every tile composing the mole sprite
 */
static void
move_mole_sprite(void)
{
    move_sprite(0, MG3_BIRD_X, fbird.bird_y);
    move_sprite(1, MG3_BIRD_X + MG3_PX_TO_TILE, fbird.bird_y);
    move_sprite(2, MG3_BIRD_X, fbird.bird_y + MG3_PX_TO_TILE);
    move_sprite(3, MG3_BIRD_X + MG3_PX_TO_TILE, fbird.bird_y + MG3_PX_TO_TILE);
}

/**
 * @brief Draw a single column of a pipe on the background
 *
 * @param pipe pointer to the pipe to draw
 * @param actual_col background column index to draw on (0-31)
 */
static void
draw_color_pipe(IN pipe_t *pipe,
                IN UINT8 actual_col,
                IN UINT8 col_index)
{
    UINT8 tile = (col_index == 0) ? FLAPPY_TILE_PIPE_LEFT : FLAPPY_TILE_PIPE_RIGHT;

    for (UINT8 row = 2; row < COMMON_SCREEN_HEIGHT_TILES; row++) {
        if (row < pipe->pipe_y || row >= pipe->pipe_y + MG3_PIPE_GAP)
            set_bkg_tile_xy(actual_col, row, tile);
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
        draw_color_pipe(pipe, actual_col, col);
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
    UINT8 bird_top_tile = (fbird.bird_y - MG3_SPRITE_Y_OFFSET) / MG3_PX_TO_TILE;
    UINT8 bird_bottom_tile =
        (fbird.bird_y - MG3_SPRITE_Y_OFFSET + MG3_BIRD_HEIGHT_PX - 1) / MG3_PX_TO_TILE;
    INT16 bird_left = MG3_BIRD_X;
    INT16 bird_right = MG3_BIRD_X + MG3_BIRD_WIDTH_PX - 1;
    INT16 pipe_left = 0;
    INT16 pipe_right = 0;

    for (UINT8 i = 0; i < MG3_NB_PIPE; i++) {
        pipe_left = fbird.pipes[i].pipe_x;
        pipe_right = pipe_left + (MG3_PIPE_WIDTH * MG3_PX_TO_TILE) - 1;
        if (bird_right < pipe_left || bird_left > pipe_right)
            continue;
        if (bird_top_tile < fbird.pipes[i].pipe_y ||
            bird_bottom_tile >= fbird.pipes[i].pipe_y + MG3_PIPE_GAP)
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
 * @brief Draw the current score value in the HUD
 */
static void
draw_score(IN game_t *game)
{
    CHAR buf[4];
    text_render_t render;

    render.text = buf;
    render.x = MG3_HUD_SCORE_VAL_X;
    render.y = MG3_HUD_ROW;

    if (game->score_mg3 != fbird.last_score) {
        uint_to_str(game->score_mg3, buf, 3);
        text_renderer_draw(&render);
        fbird.last_score = game->score_mg3;
    }
}

/**
 * @brief Draw the current level value in the HUD
 */
static void
draw_level(IN game_t *game)
{
    CHAR buf[3];
    text_render_t render;

    render.text = buf;
    render.x = MG3_HUD_LVL_VAL_X;
    render.y = MG3_HUD_ROW;

    if (game->level != fbird.last_speed) {
        uint_to_str(game->level, buf, 2);
        text_renderer_draw(&render);
        fbird.last_speed = game->level;
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
            game->score_mg3++;
            if (game->score_mg3 % MG3_PIPE_SPEED_STEP == 0) {
                game->level++;
                fbird.pipe_speed = MG3_SPEED_FROM_LEVEL(game->level);
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
    text_render_t label;
    UINT8 i = 0;

    game->level = MG3_PIPE_SPEED_INIT;
    fbird.last_score = (UINT16)(-1);
    fbird.last_speed = (UINT8)(-1);
    fbird.bird_y = MG3_SCREEN_Y_PX / 2;
    game->score_mg3 = 0;
    fbird.pipe_speed = MG3_PIPE_SPEED_INIT;

    for (i = 0; i < MG3_NB_PIPE; i++) {
        fbird.pipes[i].pipe_x = MG3_SCREEN_X_PX + (i * MG3_PIPE_SPACING);
        fbird.pipes[i].pipe_y = next_pipe_y();
    }
    set_bkg_data(0, FLAPPY_TILE_COUNT, flappy_tiles);
    set_bkg_tiles(0, 0, COMMON_SCREEN_WIDTH_TILES, COMMON_SCREEN_HEIGHT_TILES, flappy_bg_map);
    set_sprite_data(0, 4, mole_plane_1);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    move_mole_sprite();
    text_renderer_init();
    label.y = MG3_HUD_ROW;
    label.text = "SCORE";
    label.x = MG3_HUD_SCORE_LABEL_X;
    text_renderer_draw(&label);
    label.text = "LVL";
    label.x = MG3_HUD_LVL_LABEL_X;
    text_renderer_draw(&label);
    draw_score(game);
    draw_level(game);
}

void
update_flappybird(OUT game_t *game)
{
    draw_score(game);
    draw_level(game);
    if (check_collision() || fbird.bird_y >= MG3_BIRD_FLOOR_Y) {
        game_changer(game, GAME_STATE_LOBBY, TRUE);
        return;
    }
    fbird.bird_y += 1;
    move_mole_sprite();
    update_pipes(game);
}

void
handle_input_flappybird(OUT game_t *game,
                        IN UINT8 keys)
{
    (void)game;
    if (keys & J_A) {
        fbird.bird_y -= MG3_JUMP_INIT;
        if (fbird.bird_y < MG3_SPRITE_Y_OFFSET)
            fbird.bird_y = MG3_SPRITE_Y_OFFSET;
    }
}
