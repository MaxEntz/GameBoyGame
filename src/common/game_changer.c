/*
** EPITECH PROJECT, 2025
** GameBoyGame
** File description:
** game_changer.c
*/

#include "common/game_changer.h"
#include "main/core.h"

void game_changer(game_t *game, game_state_t new_game)
{
    if (game->state == new_game)
        return;
    if (new_game >= GAME_STATE_COUNT)
        return;
    transition_sound(0);
    transition_fade_out();
    game->state = new_game;
    game->state_changed = TRUE;
    change_scene(game);
    delay(300);
    transition_fade_in();
}
