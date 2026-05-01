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
    (void)game;
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
    piece_draw(&curr_piece);
}

void
update_tetris(OUT game_t *game)
{
    (void)game;
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
        if (grid_clear_lines() > 0)
            grid_draw_playfield();
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
