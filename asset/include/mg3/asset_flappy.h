/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** asset_flappy.h
*/

#ifndef ASSET_FLAPPY_H_
#define ASSET_FLAPPY_H_

    #include "common/project_types.h"

enum flappy_tile_id_e {
    FLAPPY_TILE_EMPTY = 0,
    FLAPPY_TILE_PIPE = 1,
    FLAPPY_TILE_BIRD = 2,
    FLAPPY_TILE_COUNT = 3
};

extern const UINT8 flappy_tiles[];
extern const UINT8 flappy_bg_map[];

#endif /* ASSET_FLAPPY_H_ */
