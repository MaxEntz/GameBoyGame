/*
** EPITECH PROJECT, 2025
** GameBoyGame
** File description:
** game_changer.c
*/

#ifndef GAME_CHANGER_C
#define GAME_CHANGER_C

#include "common/common.h"
#include "common/transition.h"
#include <stdbool.h>

/**
 * @brief Change the game state with a transition effect
 * 
 * @param game Pointer to the game structure
 * @param new_state The new game state to switch to
 * @return true if the state was changed, false otherwise (use to change the state in the game handler)
 */
bool game_changer(game_t *game, game_state_t new_state);

#endif /* GAME_CHANGER_C */