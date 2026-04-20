/*
** EPITECH PROJECT, 2025
** GameBoyGame
** File description:
** game_changer.h
*/

#ifndef GAME_CHANGER_H
#define GAME_CHANGER_H

#include "common/common.h"
#include "common/transition.h"

/**
 * @brief Change the game state with a transition effect
 * 
 * @param game Pointer to the game structure
 * @param new_state The new game state to switch to
 * @return void
 */
void game_changer(game_t *game, game_state_t new_state);

#endif /* GAME_CHANGER_H */
