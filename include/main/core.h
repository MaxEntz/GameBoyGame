/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** core.h
*/

#ifndef CORE_H_
    #define CORE_H_

    #include <gb/gb.h>
    #include "common/common.h"

    #include "asset_lobby.h"


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