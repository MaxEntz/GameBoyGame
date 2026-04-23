/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** asset_dialogue.h
*/

#ifndef ASSET_DIALOGUE_H_
    #define ASSET_DIALOGUE_H_

    #include "common/project_types.h"

    #define DIALOGUE_TILE_BASE 165U  // Instant after font tiles (128 + 37)

/**
 * @brief Tile indices within the dialogue_box_tiles array
 */
enum dialogue_tile_e {
    DTILE_FILL,
    DTILE_TL,
    DTILE_TR,
    DTILE_BL,
    DTILE_ARROW,
    DTILE_TOP,
    DTILE_BOT,
    DTILE_LEFT,
    DTILE_RIGHT,
    DTILE_COUNT
};

extern const UINT8 dialogue_box_tiles[];
extern const UINT8 dialogue_box_map[];

#endif /* !ASSET_DIALOGUE_H_ */
