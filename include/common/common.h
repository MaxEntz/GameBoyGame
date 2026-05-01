/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** common.h
*/

#ifndef COMMON_H_
    #define COMMON_H_

    #include <gb/gb.h>
    #include "project_types.h"

    #define MAX_STATES GAME_STATE_COUNT
    #define COMMON_SCREEN_WIDTH_TILES 20U               //20 tiles of 8 pixels = 160 pixels
    #define COMMON_SCREEN_HEIGHT_TILES 18U              //18 tiles of 8 pixels = 144 pixels

    #define MOVING_SENS_UP 6
    #define MOVING_SENS_DOWN 0
    #define MOVING_SENS_LEFT 12
    #define MOVING_SENS_RIGHT 18

/**
 * @brief Enum to represent different game states
 */
typedef enum {
    GAME_STATE_LOBBY,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_VICTORY,
    GAME_STATE_MG1,
    GAME_STATE_MG2,
    GAME_STATE_MG3,
    GAME_STATE_GAME_OVER,
    GAME_STATE_COUNT
} game_state_t;

/**
 * @brief Structure to manage the game state
 * And the player position for now, but we can add more stuff later
 * Like the score, the health, etc...
 */
typedef struct game_s {
    game_state_t state;
    BOOLEAN      is_running;
    BOOLEAN      state_changed;
    UINT8        fps_counter;
    UINT16       seconds_counter;
    UINT8        player_x;
    UINT8        player_y;
    BOOLEAN      is_moving;
    UINT8        moving_dir;
} game_t;

/**
 * @brief Structure to manage different game states
 * And the functions to call for each state
 */
typedef struct management_state_s {
    game_state_t state;
    void (*load_assets)(game_t *game);
    void (*handle_input)(game_t *game, UINT8 keys);
    void (*update)(game_t *game);
} management_state_t;

#endif /* !COMMON_H_ */
