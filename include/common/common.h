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

    // To update... about your game
    #define MASTER_SCORE_EASY_MG1 100
    #define MASTER_SCORE_EASY_MG2 1500
    #define MASTER_SCORE_EASY_MG3 100

    #define MASTER_SCORE_MEDIUM_MG1 200
    #define MASTER_SCORE_MEDIUM_MG2 2000
    #define MASTER_SCORE_MEDIUM_MG3 200

    #define MASTER_SCORE_HARD_MG1 600
    #define MASTER_SCORE_HARD_MG2 3000
    #define MASTER_SCORE_HARD_MG3 700

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
    GAME_STATE_MENU,
    GAME_STATE_SAVE_SELECT,
    GAME_STATE_CHOOSE_DIFFICULTY,
    GAME_STATE_COUNT
} game_state_t;

typedef enum map_id_e {
    MAP_ID_TL = 1,
    MAP_ID_TC = 2,
    MAP_ID_TR = 3,
    MAP_ID_CL = 4,
    MAP_ID_CC = 5,
    MAP_ID_CR = 6,
    MAP_ID_BL = 7,
    MAP_ID_BC = 8,
    MAP_ID_BR = 9,
    MAP_ID_INVALID = 0
} map_id_t;

typedef enum difficulty_e {
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD,
    DIFFICULTY_NOT_CHOSEN,
    DIFFICULTY_COUNT
} difficulty_t;

/**
 * @brief Structure to manage global game state and scores
 */
typedef struct game_s {
    game_state_t state;
    BOOLEAN      is_running;
    BOOLEAN      state_changed;
    UINT16       best_score_mg1;
    UINT16       best_score_mg2;
    UINT16       best_score_mg3;
    UINT16       score_mg1;
    UINT16       score_mg2;
    UINT16       score_mg3;
    UINT8        level;
    difficulty_t difficulty;
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
