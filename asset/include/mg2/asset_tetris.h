/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** asset_tetris.h
*/

#ifndef ASSET_TETRIS_H_
    #define ASSET_TETRIS_H_

    #include "common/project_types.h"

enum tetris_tile_id_e {
    TETRIS_TILE_EMPTY     = 0,
    TETRIS_TILE_BORDER    = 1,
    TETRIS_TILE_BLOCK_I   = 2,
    TETRIS_TILE_BLOCK_O   = 3,
    TETRIS_TILE_BLOCK_T   = 4,
    TETRIS_TILE_BLOCK_S   = 5,
    TETRIS_TILE_BLOCK_Z   = 6,
    TETRIS_TILE_BLOCK_J   = 7,
    TETRIS_TILE_BLOCK_L   = 8,
    TETRIS_TILE_COUNT     = 9
};

#define TETRIS_TILE_SIZE 16u

extern const UINT8 tetris_tiles[];

extern const UINT8 tetris_tile_empty[];
extern const UINT8 tetris_tile_border[];
extern const UINT8 tetris_tile_block_i[];
extern const UINT8 tetris_tile_block_o[];
extern const UINT8 tetris_tile_block_t[];
extern const UINT8 tetris_tile_block_s[];
extern const UINT8 tetris_tile_block_z[];
extern const UINT8 tetris_tile_block_j[];
extern const UINT8 tetris_tile_block_l[];

#endif /* !ASSET_TETRIS_H_ */
