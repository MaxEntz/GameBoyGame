/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris.c
*/

#include "mg2/tetris.h"
#include "common/game_changer.h"

static piece_t curr_piece;
static UINT8   delay_frame;
static UINT8   move_frame;
static UINT8   cleared_lines;

static const UINT16 score_table[5] = {0, 100, 300, 500, 800};

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
 * @brief Advance to the next piece in the cycle (I->O->T->S->Z->J->L->I)
 *
 * only temp until i implement the randomness
 */
static void
spawn_next(void)
{
    curr_piece.type = (curr_piece.type + 1) % PIECE_COUNT;
    curr_piece.x = PIECE_SPAWN_X;
    curr_piece.y = PIECE_SPAWN_Y;
    curr_piece.rot = 0;
    curr_piece.can_rotate = TRUE;
}

void
tetris(OUT game_t *game)
{
    game->score_mg2 = 0;
    game->level = 1;
    cleared_lines = 0;
    grid_init();
    delay_frame = 0;
    move_frame = 0;
    curr_piece.type = PIECE_I;
    curr_piece.x = PIECE_SPAWN_X;
    curr_piece.y = PIECE_SPAWN_Y;
    curr_piece.rot = 0;
    curr_piece.can_rotate = TRUE;
    move_sprite(0, 0, 0);
    set_bkg_data(0, TETRIS_TILE_COUNT, tetris_tiles);
    text_renderer_init();
    set_bkg_tiles(0, 0, 20, 18, tetris_bg_map);
    draw_hud(0, 1, 0);
    piece_draw(&curr_piece);
}

void
update_tetris(OUT game_t *game)
{
    UINT8 cleared;
    UINT8 new_level;

    if (move_frame > 0)
        move_frame--;
    delay_frame++;
    if (delay_frame < get_drop_delay(game->level))
        return;
    delay_frame = 0;
    if (piece_can_move_down(&curr_piece)) {
        piece_erase(&curr_piece);
        curr_piece.y++;
        piece_draw(&curr_piece);
    } else {
        piece_lock(&curr_piece);
        cleared = grid_clear_lines();
        if (cleared > 0) {
            grid_draw_playfield();
            game->score_mg2 += (INT16)(score_table[cleared] * game->level);
            cleared_lines += cleared;
            new_level = (UINT8)(1 + cleared_lines / LINES_PER_LEVEL);
            if (new_level != game->level) {
                game->level = new_level;
                draw_level(game->level);
            }
            draw_score(game->score_mg2);
            draw_lines(cleared_lines);
        }
        spawn_next();
        piece_draw(&curr_piece);
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
        curr_piece.can_rotate = TRUE;
    if (curr_piece.can_rotate) {
        if (keys & J_A) {
            rotate_r(&curr_piece);
            curr_piece.can_rotate = FALSE;
        } else if (keys & J_B) {
            rotate_l(&curr_piece);
            curr_piece.can_rotate = FALSE;
        }
    }
    if (keys & J_DOWN)
        delay_frame += (DROP_DELAY_BASE / 4);
    if (move_frame == 0) {
        if (keys & J_LEFT) {
            if (piece_can_move_left(&curr_piece)) {
                piece_erase(&curr_piece);
                curr_piece.x--;
                piece_draw(&curr_piece);
                move_frame = MOVE_DELAY;
            }
        } else if (keys & J_RIGHT) {
            if (piece_can_move_right(&curr_piece)) {
                piece_erase(&curr_piece);
                curr_piece.x++;
                piece_draw(&curr_piece);
                move_frame = MOVE_DELAY;
            }
        }
    }
}
