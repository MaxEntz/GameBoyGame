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
 * @brief Change the scene if the state has changed
 */
void
change_scene(OUT game_t *game);

#endif /* !CORE_H_ */   