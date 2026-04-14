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

typedef struct game_s {
    game_state_t state;
} game_t;

/**
 * @brief Main game loop
 * This funciton is the base of all the game,
 * Just call one time and until the end of the game.
 * @param void
 * @return void
 */
void
core(void);

/**
 * @brief Set the display object
 * @param display Boolean to turn on/off the display
 * @param sprite Boolean to show/hide sprites
 * @param bkg Boolean to show/hide background
 * @param win Boolean to show/hide window layer UI
 * @return void
 */
void
set_display(BOOLEAN display,
            BOOLEAN sprite,
            BOOLEAN bkg,
            BOOLEAN win);

#endif /* !CORE_H_ */   