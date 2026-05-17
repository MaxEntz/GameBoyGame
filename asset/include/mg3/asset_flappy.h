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
    FLAPPY_TILE_EMPTY      = 0,
    FLAPPY_TILE_PIPE_LEFT  = 1,
    FLAPPY_TILE_PIPE_RIGHT = 2,
    FLAPPY_TILE_BIRD       = 3,
    FLAPPY_TILE_HUD_BL     = 4,
    FLAPPY_TILE_HUD_BR     = 5,
    FLAPPY_TILE_HUD_HB     = 6,
    FLAPPY_TILE_HUD_VL     = 7,
    FLAPPY_TILE_HUD_VR     = 8,
    FLAPPY_TILE_COUNT      = 9
};

extern const UINT8 mole_plane_1[];
extern const UINT8 flappy_tiles[];
extern const UINT8 flappy_bg_map[];

#endif /* ASSET_FLAPPY_H_ */
