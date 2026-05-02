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

static const text_render_t mg2_labels[] = {
    {"SCORE", MG2_SCORE_LABEL_X, MG2_SCORE_LABEL_Y},
    {"LEVEL", MG2_LEVEL_LABEL_X, MG2_LEVEL_LABEL_Y},
    {"LINES", MG2_LINES_LABEL_X, MG2_LINES_LABEL_Y},
    {NULL,    0,                 0}
};

static const UINT16 score_table[5] = {0, 100, 300, 500, 800};


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

/**
 * @brief Draw all static HUD labels on the background
 */
static void
draw_hud(void)
{
    UINT8 i = 0;

    while (mg2_labels[i].text != NULL)
        text_renderer_draw(&mg2_labels[i++]);
}

/**
 * @brief Draw the current score value on the HUD
 * 
 * @param score Score value to draw
 */
static void
draw_score(INT16 score)
{
    CHAR          buf[7];
    text_render_t render = {buf, MG2_SCORE_VAL_X, MG2_SCORE_VAL_Y};

    uint_to_str((UINT16)score, buf, 6);
    text_renderer_draw(&render);
}

static void
draw_lines(UINT8 lines)
{
    CHAR          buf[4];
    text_render_t render = {buf, MG2_LINES_VAL_X, MG2_LINES_VAL_Y};

    uint_to_str((UINT16)lines, buf, 3);
    text_renderer_draw(&render);
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
    draw_hud();
    draw_score(0);
    draw_lines(0);
    piece_draw(&curr_piece);
}

void
update_tetris(OUT game_t *game)
{
    UINT8 cleared;

    if (move_frame > 0)
        move_frame--;
    delay_frame++;
    if (delay_frame < DROP_DELAY)
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
        delay_frame += (DROP_DELAY / 4);
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
