/*
** EPITECH PROJECT, 2025
** GameBoyGame
** File description:
** game_changer.c
*/

#include "common/game_changer.h"

bool game_changer(game_t *game, game_state_t new_game)
{
    if (game->state == new_game)
        return FALSE;
    if (new_game >= GAME_STATE_COUNT)
        return FALSE;
    transition_sound(0);
    transition_fade_out();
    game->state = new_game;
    delay(500);
    transition_fade_in();
    return TRUE;
}