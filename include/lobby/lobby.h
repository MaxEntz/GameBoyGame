/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lobby.h
*/

#ifndef LOBBY_H_
    #define LOBBY_H_

    #include "asset_lobby.h"
    #include "common/common.h"
    #include "common/game_changer.h"
    #include "common/transition.h"

    // Map manager macro
    #define MAP_LEFT (-1)
    #define MAP_RIGHT (1)
    #define MAP_UP (-3)
    #define MAP_DOWN (3)

typedef enum transition_dir_e {
    TRANSITION_TB,
    TRANSITION_BT,
    TRANSITION_LR,
    TRANSITION_RL
} transition_dir_t;

typedef struct map_manager_s {
    map_id_t id_map;
    const UINT8 *map_data;
} map_manager_t;

typedef struct lobby_state_s {
    UINT8    fps_counter;
    UINT16   seconds_counter;
    UINT8    player_x;
    UINT8    player_y;
    BOOLEAN  is_moving;
    UINT8    moving_dir;
    BOOLEAN  is_changing_map;
    UINT8    current_map[20 * 18];
    map_id_t current_map_id;
    BOOLEAN  rng_initialized;
} lobby_state_t;

void
lobby_init_state(void);

lobby_state_t
*lobby_get_state(void);

/**
 * @brief Load the lobby assets and handle the lobby state
 * We can see it like a creator in CPP
 * @param game Pointer to the game structure
 * @return void
 */
void
lobby(OUT game_t *game);

/**
 * @brief Handle the input in the lobby state
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_lobby(OUT game_t *game,
                   IN UINT8 keys);

/**
 * @brief Update the lobby state
 * @param game Pointer to the game structure
 * @return void
 */
void
update_lobby(OUT game_t *game);

/**
 * @brief Handle the map transition animation
 * @param game Pointer to the game structure
 * @return void
 */
void
transition_map_animation(OUT game_t *game,
                         IN transition_dir_t dir);

/**
 * @brief Switch the map based on the player's position and the tile they are on
 * @param game Pointer to the game structure
 * @param x The x coordinate of the player
 * @param y The y coordinate of the player
 * @param tile The tile the player is on
 * @return TRUE if the map is switched, FALSE otherwise
 */
BOOLEAN
switch_map(game_t *game,
           INT16 x,
           INT16 y,
           UINT8 tile);

#endif /* !LOBBY_H_ */
