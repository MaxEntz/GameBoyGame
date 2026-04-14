/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** core.h
*/

#ifndef CORE_H_
    #define CORE_H_

    #include <gb/gb.h>
    #include "project_types.h"

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_VICTORY,
    GAME_STATE_MG1,
    GAME_STATE_MG2,
    GAME_STATE_MG3,
    GAME_STATE_GAME_OVER
} game_state_t;

/**
 * @brief Main game loop
 * This funciton is the base of all the game,
 * Just call one time and until the end of the game.
 * @param void
 * @return void
 */
void
core(void);

#endif /* !CORE_H_ */   