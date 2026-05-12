/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** get_tile_by_map.h
*/

#ifndef GET_TILE_BY_MAP_H_
    #define GET_TILE_BY_MAP_H_

    #include "common/common.h"

/**
 * @brief Get the tile at the specified position in the map
 * @param map Pointer to the map array
 * @param x X coordinate
 * @param y Y coordinate
 * @return The tile at the specified position
 */
UINT8
get_tile_by_map(IN const UINT8 map[COMMON_SCREEN_WIDTH_TILES * COMMON_SCREEN_HEIGHT_TILES], INT16 x, INT16 y);

#endif /* GET_TILE_BY_MAP_H_ */
