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

    #define MAX_STATES 8

typedef enum {
    GAME_STATE_LOBBY,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_VICTORY,
    GAME_STATE_MG1,
    GAME_STATE_MG2,
    GAME_STATE_MG3,
    GAME_STATE_GAME_OVER
} game_state_t;

typedef struct game_s {
    game_state_t state;
    BOOLEAN      is_running;
    BOOLEAN      state_changed;
    UINT8        player_x;
    UINT8        player_y;
} game_t;

typedef struct management_state_s {
    game_state_t state;
    void (*load_assets)(game_t *game);
    void (*handle_input)(game_t *game, UINT8 keys);
    void (*update)(game_t *game);
} management_state_t;

#endif /* !COMMON_H_ */