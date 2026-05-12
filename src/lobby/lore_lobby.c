/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lore_lobby.c
*/

#include "lobby/lobby.h"
#include "lobby/lore_lobby.h"
#include "common/game_changer.h"

static const CHAR *g_dialogue_texts[NB_DIALOGUES] = {
    "Welcome\nlittle Mole!\nBeat me and my bro\nat our games\nto escape the\nisland!",
    "Haha!\n Gotcha!\nWanna try again?",
    "Ouch!\n \nWell done little\nmole\nfind my bro\non the right side\n",
    "You beat my bro?\nImpressive!\nBut can you beat\nme?",
    "Pfff!\n \nDid you really\nbeat my bro ?\n You're not good\n enough !",
    "Noooooo!\n \nYou beat us both?\nImpossible!\nWell done little\nmole, you can\nleave the island",
    "Wait!\n \nYou want to leave?\n\nSure, \nbut I warn you,\nI won't go easy\n on you!\n"
};

void
lore_start_dialogue(OUT game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();

    if (lobby->dialogue_index >= NB_DIALOGUES)
        return;
    if (dialogue_is_active(&lobby->dialogue))
        return;
    if (lobby->dialogue_index == 1 && game->score_mg2 >= MASTER_SCORE_MG2)
        lobby->dialogue_index = 2;
    else if (lobby->dialogue_index == 4 && game->score_mg2 >= MASTER_SCORE_MG2)
        lobby->dialogue_index = 5;
    dialogue_start(&lobby->dialogue, g_dialogue_texts[lobby->dialogue_index]);
}

void
lore_update(OUT game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();
    dialogue_t *dlg = &lobby->dialogue;

    if (lobby->dialogue_index >= NB_DIALOGUES)
        return;
    if (lobby->should_dialogue) {
        lobby->should_dialogue = FALSE;
        if (lobby->dialogue_index == 1 || lobby->dialogue_index == 4)
            lore_start_dialogue(game);
    }
    if (lobby->dialogue_index == 6 && lobby->current_map_id == MAP_ID_CC
            && !dialogue_is_active(dlg))
        lore_start_dialogue(game);
    dialogue_update(dlg);
    if (dialogue_is_active(dlg) || dlg->chars_shown == 0)
        return;
    dlg->chars_shown = 0;
    if (lobby->dialogue_index == 0) {
        lobby->dialogue_index = 1;
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    }
    if (lobby->dialogue_index == 1 || lobby->dialogue_index == 4) {
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    }
    if (lobby->dialogue_index == 3) {
        lobby->dialogue_index = 4;
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    }
    lobby->dialogue_index++;
}
