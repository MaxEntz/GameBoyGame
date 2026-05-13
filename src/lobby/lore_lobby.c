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
    "Noooooo!\n \nYou beat us both?\nImpossible!\nWell done little\nmole, you can\nleave the island\nFind the hole\nin the center!",
    "Wait!\n \nYou want to leave?\n\nSure, \nbut I warn you,\nI won't go easy\n on you!\n",
    "Too slow!\n \nYou won't escape\nthat easily!\nTry again!",
    "Incredible...\n \nYou truly earned\nyour freedom!\nGoodbye little\nmole!"
};

/**
 * @brief Advance dialogue_index to the win branch if the score threshold is met
 */
static void
check_win(INOUT lobby_state_t *lobby, IN game_t *game)
{
    if (lobby->dialogue_index == 1 && game->score_mg2 >= MASTER_SCORE_MG2)
        lobby->dialogue_index = 2;
    else if (lobby->dialogue_index == 4 && game->score_mg2 >= MASTER_SCORE_MG2)
        lobby->dialogue_index = 5;
    else if (lobby->dialogue_index == 7 && game->score_mg2 >= MASTER_SCORE_MG2)
        lobby->dialogue_index = 8;
}

/**
 * @brief Handle automatic dialogue triggers: returning from game and center room entry
 */
static void
check_auto(INOUT game_t *game, INOUT lobby_state_t *lobby,
                    IN dialogue_t *dlg)
{
    if (lobby->should_dialogue) {
        lobby->should_dialogue = FALSE;
        if (lobby->dialogue_index == 1 || lobby->dialogue_index == 4
                || lobby->dialogue_index == 7)
            lore_start_dialogue(game);
    }
    if (lobby->dialogue_index == 6 && lobby->current_map_id == MAP_ID_CC
            && !dialogue_is_active(dlg) && dlg->chars_shown == 0) {
        lobby->player_y = 72;
        lore_start_dialogue(game);
    }
}

/**
 * @brief Handle state transitions after a dialogue completes
 */
static void
handle_dialogue_end(INOUT game_t *game, INOUT lobby_state_t *lobby)
{
    if (lobby->dialogue_index == 0) {
        lobby->dialogue_index = 1;
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    }
    if (lobby->dialogue_index == 1 || lobby->dialogue_index == 4
            || lobby->dialogue_index == 7) {
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    }
    if (lobby->dialogue_index == 3 || lobby->dialogue_index == 6) {
        lobby->dialogue_index++;
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    }
    lobby->dialogue_index++;
}

void
lore_start_dialogue(OUT game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();

    if (lobby->dialogue_index >= NB_DIALOGUES)
        return;
    if (dialogue_is_active(&lobby->dialogue))
        return;
    check_win(lobby, game);
    dialogue_start(&lobby->dialogue, g_dialogue_texts[lobby->dialogue_index]);
}

void
lore_update(OUT game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();
    dialogue_t *dlg = &lobby->dialogue;

    if (lobby->dialogue_index >= NB_DIALOGUES)
        return;
    check_auto(game, lobby, dlg);
    dialogue_update(dlg);
    if (dialogue_is_active(dlg) || dlg->chars_shown == 0)
        return;
    dlg->chars_shown = 0;
    handle_dialogue_end(game, lobby);
}
