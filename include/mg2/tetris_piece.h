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
    INT8    x;
    UINT8   y;
    UINT8   rot;
    BOOLEAN can_rotate;
} piece_t;

extern const UINT8 piece_shapes[PIECE_COUNT][4][4][4];

/**
 * @brief Draw the piece on the playfield
 * 
 * @param piece piece to draw
 */
void
piece_draw(IN const piece_t *piece);

/**
 * @brief Erase the piece from the playfield (draw empty tiles)
 * 
 * @param piece piece to erase
 */
void
piece_erase(IN const piece_t *piece);

/**
 * @brief Check if the piece can move down
 * 
 * @param piece piece to check
 * @return TRUE if the piece can move down, FALSE otherwise
 */
BOOLEAN
piece_can_move_down(IN const piece_t *piece);

/**
 * @brief Check if the piece can move left
 * 
 * @param piece piece to check
 * @return TRUE if the piece can move left, FALSE otherwise
 */
BOOLEAN
piece_can_move_left(IN const piece_t *piece);

/**
 * @brief Check if the piece can move right
 * 
 * @param piece piece to check
 * @return TRUE if the piece can move right, FALSE otherwise
 */
BOOLEAN
piece_can_move_right(IN const piece_t *piece);

/**
 * @brief Write the piece's tiles to the grid
 * 
 * @param piece piece to lock
 */
void
piece_lock(IN const piece_t *piece);

/**
 * @brief Check if the piece can spawn at its initial position
 * 
 * @param piece piece to check
 * @return TRUE if the piece can spawn, FALSE otherwise
 */
BOOLEAN
piece_can_spawn(IN const piece_t *piece);

/**
 * @brief Rotate the piece clockwise if possible, with basic wall addapation
 * 
 * @param piece piece to rotate
 */
void
rotate_r(INOUT piece_t *piece);

/**
 * @brief Rotate the piece counter-clockwise if possible, with basic wall addapation
 *
 * @param piece piece to rotate
 */
void
rotate_l(INOUT piece_t *piece);

#endif /* !TETRIS_PIECE_H_ */
