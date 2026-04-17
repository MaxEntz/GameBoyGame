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
    BOOLEAN is_running;
    BOOLEAN state_changed;
} game_t;

typedef struct asset_loading_s {
    game_state_t state;
    void (*load_assets)(game_t *game);
} asset_loading_t;

#endif /* !COMMON_H_ */