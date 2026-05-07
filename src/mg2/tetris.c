/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris.c
*/

#include "mg2/tetris.h"
#include "common/game_changer.h"

static tetris_t        g_tetris;
static const UINT16    score_table[5] = {0, 100, 300, 500, 800};

/**
 * @brief Spawn the queued piece and pick the next one randomly
 */
static void
spawn_next(void)
{
    g_tetris.curr_piece.type = g_tetris.next_type;
    g_tetris.curr_piece.x = PIECE_SPAWN_X;
    g_tetris.curr_piece.y = PIECE_SPAWN_Y;
    g_tetris.curr_piece.rot = 0;
    g_tetris.curr_piece.can_rotate = TRUE;
    g_tetris.next_type = (piece_type_t)random_get(PIECE_COUNT);
    draw_next_piece(g_tetris.next_type);
}

/**
 * @brief calculates the drop delay in frames for the given level
 * 
 * @param level level number
 * @return drop delay in frames
 */
static UINT8
get_drop_delay(UINT8 level)
{
    UINT8 reduction = (UINT8)((level - 1) * DROP_DELAY_STEP);

    if (reduction >= DROP_DELAY_BASE - DROP_DELAY_MIN)
        return DROP_DELAY_MIN;
    return (UINT8)(DROP_DELAY_BASE - reduction);
}

/**
 * @brief Lock the current piece, clear lines, update score/level, spawn next
 * 
 * @param game current game state
 */
static void
handle_piece_lock(OUT game_t *game)
{
    UINT8 cleared;
    UINT8 new_level;

    piece_lock(&g_tetris.curr_piece);
    cleared = grid_clear_lines();
    if (cleared > 0) {
        grid_draw_playfield();
        game->score_mg2 += (INT16)(score_table[cleared] * game->level);
        g_tetris.cleared_lines += cleared;
        new_level = (UINT8)(1 + g_tetris.cleared_lines / LINES_PER_LEVEL);
        if (new_level != game->level) {
            game->level = new_level;
            draw_level(game->level);
        }
        draw_score(game->score_mg2);
        draw_lines(g_tetris.cleared_lines);
    }
    spawn_next();
    if (!piece_can_spawn(&g_tetris.curr_piece))
        game_changer(game, GAME_STATE_LOBBY);
    else
        piece_draw(&g_tetris.curr_piece);
}

/**
 * @brief Handle left/right movement with move_frame throttle
 * 
 * @param keys current input keys
 */
static void
handle_left_right(IN UINT8 keys)
{
    if (g_tetris.move_frame != 0)
        return;
    if (keys & J_LEFT) {
        if (piece_can_move_left(&g_tetris.curr_piece)) {
            piece_erase(&g_tetris.curr_piece);
            g_tetris.curr_piece.x--;
            piece_draw(&g_tetris.curr_piece);
            g_tetris.move_frame = MOVE_DELAY;
        }
    } else if (keys & J_RIGHT) {
        if (piece_can_move_right(&g_tetris.curr_piece)) {
            piece_erase(&g_tetris.curr_piece);
            g_tetris.curr_piece.x++;
            piece_draw(&g_tetris.curr_piece);
            g_tetris.move_frame = MOVE_DELAY;
        }
    }
}

void
tetris(OUT game_t *game)
{
    game->score_mg2 = 0;
    game->level = 1;
    g_tetris.cleared_lines = 0;
    g_tetris.delay_frame = 0;
    g_tetris.move_frame = 0;
    g_tetris.next_type = (piece_type_t)random_get(PIECE_COUNT);
    grid_init();
    for (UINT8 i = 0; i < 4; i++)
        move_sprite(i, 0, 0);
    set_bkg_data(0, TETRIS_TILE_COUNT, tetris_tiles);
    text_renderer_init();
    set_bkg_tiles(0, 0, 20, 18, tetris_bg_map);
    draw_hud(0, 1, 0);
    spawn_next();
    piece_draw(&g_tetris.curr_piece);
}

void
update_tetris(OUT game_t *game)
{
    if (g_tetris.move_frame > 0)
        g_tetris.move_frame--;
    g_tetris.delay_frame++;
    if (g_tetris.delay_frame < get_drop_delay(game->level))
        return;
    g_tetris.delay_frame = 0;
    if (piece_can_move_down(&g_tetris.curr_piece)) {
        piece_erase(&g_tetris.curr_piece);
        g_tetris.curr_piece.y++;
        piece_draw(&g_tetris.curr_piece);
    } else {
        handle_piece_lock(game);
    }
}

void
handle_input_tetris(OUT game_t *game,
                   IN UINT8 keys)
{
    if (keys & J_SELECT) {
        game_changer(game, GAME_STATE_LOBBY);
        return;
    }
    if (!(keys & (J_A | J_B)))
        g_tetris.curr_piece.can_rotate = TRUE;
    if (g_tetris.curr_piece.can_rotate) {
        if (keys & J_A) {
            rotate_r(&g_tetris.curr_piece);
            g_tetris.curr_piece.can_rotate = FALSE;
        } else if (keys & J_B) {
            rotate_l(&g_tetris.curr_piece);
            g_tetris.curr_piece.can_rotate = FALSE;
        }
    }
    if (keys & J_DOWN)
        g_tetris.delay_frame += (DROP_DELAY_BASE / 4);
    handle_left_right(keys);
}
