/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** trap_memory.h
*/

#ifndef TRAP_MEMORY_H_
    #define TRAP_MEMORY_H_

    #include "common/common.h"
    #include "common/game_changer.h"
    #include "common/text_renderer.h"
    #include "common/random.h"
    #include "common/get_tile_by_map.h"
    #include "asset_lobby.h"
    #include "mg1/asset_tm.h"

    #define OFFSET_SAFER_TILE 90

typedef struct trap_memory_s {
    UINT8      player_x;
    UINT8      player_y;
    BOOLEAN    is_moving;
    UINT8      moving_dir;
    UINT8      fps_counter;
    UINT16     seconds_counter;
    UINT16     time_round;
    UINT8      nb_safe_tiles;
    BOOLEAN    hud_ready;
    UINT16     last_score;
    UINT8      last_level;
    UINT8      current_map[COMMON_SCREEN_WIDTH_TILES * COMMON_SCREEN_HEIGHT_TILES];
} trap_memory_t;

/**
 * @brief Load the Trap Memory assets and handle its state
 * @param game Pointer to the game structure
 * @return void
 */
void
trap_memory(OUT game_t *game);

/**
 * @brief Update Trap Memory
 * @param game Pointer to the game structure
 * @return void
 */
void
update_trap_memory(OUT game_t *game);

/**
 * @brief Handle the input for Trap Memory
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_trap_memory(OUT game_t *game,
                        IN UINT8 keys);

/**
 * @brief Move the player sprite based on the current movement state
 * @param game Pointer to the game structure
 * @return void
 */
void
move_sprite_personage(OUT trap_memory_t *game);

/**
 * @brief Get the Trap Memory state
 * @return Pointer to the Trap Memory state
 */
trap_memory_t
*trap_memory_get(void);

#endif /* !TRAP_MEMORY_H_ */
