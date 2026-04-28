/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_piece.h
*/

#ifndef TETRIS_PIECE_H_
    #define TETRIS_PIECE_H_

    #include "common/project_types.h"

    #define PIECE_SPAWN_X  3
    #define PIECE_SPAWN_Y  0

typedef enum piece_type_e {
    PIECE_I     = 0,
    PIECE_O     = 1,
    PIECE_T     = 2,
    PIECE_S     = 3,
    PIECE_Z     = 4,
    PIECE_J     = 5,
    PIECE_L     = 6,
    PIECE_COUNT = 7
} piece_type_t;

typedef struct piece_s {
    piece_type_t type;
    INT8 x;
    UINT8  y;
} piece_t;

extern const UINT8 piece_shapes[PIECE_COUNT][4][4];

void    piece_draw(IN const piece_t *piece);
void    piece_erase(IN const piece_t *piece);
BOOLEAN piece_can_move_down(IN const piece_t *piece);
BOOLEAN piece_can_move_left(IN const piece_t *piece);
BOOLEAN piece_can_move_right(IN const piece_t *piece);
void    piece_lock(IN const piece_t *piece);

#endif /* !TETRIS_PIECE_H_ */
