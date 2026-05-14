/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** get_tile_by_map.c
*/

#include "common/get_tile_by_map.h"

UINT8
get_tile_by_map(IN const UINT8 map[COMMON_SCREEN_WIDTH_TILES * COMMON_SCREEN_HEIGHT_TILES], INT16 x, INT16 y)
{
    UINT8 tile_x = 0;
    UINT8 tile_y = 0;

    if (x < 0 || y < 0)
        return 0;
    tile_x = x >> 3;
    tile_y = y >> 3;
    if (tile_x >= COMMON_SCREEN_WIDTH_TILES || tile_y >= COMMON_SCREEN_HEIGHT_TILES)
        return 0;
    return map[tile_y * COMMON_SCREEN_WIDTH_TILES + tile_x];
}
