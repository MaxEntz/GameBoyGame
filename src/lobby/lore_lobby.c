/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lore_lobby.c
*/

#include "lobby/lobby.h"
#include "lobby/lore_lobby.h"
#include "common/game_changer.h"
#include "common/save.h"

static const CHAR *g_dialogue_texts[LORE_STEP_COUNT] = {
    "Ouch...\nMy head...\nThose crabs\nkidnapped me!\nI need to\nfind a way out!",
    "Welcome\nlittle Mole!\nBeat me and my bro\nat our games\nto escape the\nisland!",
    "Hahaha!\n \nToo easy!\nWanna try again?",
    "Ouch!\n \nWell done\nlittle mole!\nNow find my bro\non the right!",
    "You beat my bro?\nImpressive!\nBut can you\nbeat me?",
    "Pfff!\n \nYou beat my bro\nbut not me!\nTry harder,\nlittle mole!",
    "Noooo!\n \nYou beat us both!\nHead to the\ncenter if you\nwant to escape!",
    "The ground...\n \nIt's moving!\nI must find\nsafe tiles!",
    "Too slow!\n \nYou won't escape\nthat easily!\nTry again!",
    "Incredible...\n \nYou truly earned\nyour freedom!\nGoodbye little\nmole!"
};

/**
 * @brief Advance dialogue_index to the win branch if the score threshold is met
 */
static void
check_win(INOUT lobby_state_t *lobby, IN game_t *game)
{
    if (lobby->dialogue_index == LORE_LEFT_LOSE && game->score_mg2 >= MASTER_SCORE_MG2)
        lobby->dialogue_index = LORE_LEFT_WIN;
    else if (lobby->dialogue_index == LORE_RIGHT_LOSE && game->score_mg2 >= MASTER_SCORE_MG2) //a changer pr flappy
        lobby->dialogue_index = LORE_RIGHT_WIN;
    else if (lobby->dialogue_index == LORE_CC_LOSE && game->score_mg1 >= MASTER_SCORE_MG1)
        lobby->dialogue_index = LORE_CC_WIN;
}

/**
 * @brief Handle automatic dialogue triggers: returning from game and center room entry
 */
static void
check_auto(INOUT game_t *game, INOUT lobby_state_t *lobby,
                    IN dialogue_t *dlg)
{
    if (lobby->dialogue_index == LORE_SPAWN_INTRO && !dialogue_is_active(dlg) && dlg->chars_shown == 0)
        lore_start_dialogue(game);
    if (lobby->should_dialogue) {
        lobby->should_dialogue = FALSE;
        if (lobby->dialogue_index == LORE_LEFT_LOSE
                || lobby->dialogue_index == LORE_RIGHT_LOSE
                || lobby->dialogue_index == LORE_CC_LOSE)
            lore_start_dialogue(game);
    }
    if (lobby->dialogue_index == LORE_CC_INTRO && lobby->current_map_id == MAP_ID_CC
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
    if (lobby->dialogue_index == LORE_LEFT_INTRO) {
        lobby->dialogue_index++;
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    } else if (lobby->dialogue_index == LORE_RIGHT_INTRO) {
        lobby->dialogue_index++;
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    } else if (lobby->dialogue_index == LORE_CC_INTRO) {
        lobby->dialogue_index++;
        game_changer(game, GAME_STATE_MG1, TRUE);
        return;
    }
    if (lobby->dialogue_index == LORE_LEFT_LOSE) {
        game_changer(game, GAME_STATE_MG2, TRUE);
        return;
    }
    if (lobby->dialogue_index == LORE_RIGHT_LOSE) {
        game_changer(game, GAME_STATE_MG2, TRUE);           // a changer pr flappy
        return;
    }
    if (lobby->dialogue_index == LORE_CC_LOSE) {
        game_changer(game, GAME_STATE_MG1, TRUE);
        return;
    }
    if (lobby->dialogue_index == LORE_LEFT_WIN || lobby->dialogue_index == LORE_RIGHT_WIN) {
        lobby->dialogue_index++;
        save_write(game);
        return;
    }
    if (lobby->dialogue_index == LORE_CC_WIN) {
        lobby->dialogue_index++;
        save_write(game);
        game_changer(game, GAME_STATE_MENU, TRUE);
        return;
    }
    lobby->dialogue_index++;
}

void
lore_start_dialogue(OUT game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();

    if (lobby->dialogue_index >= LORE_STEP_COUNT)
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

    if (lobby->dialogue_index >= LORE_STEP_COUNT)
        return;
    check_auto(game, lobby, dlg);
    dialogue_update(dlg);
    if (dialogue_is_active(dlg) || dlg->chars_shown == 0)
        return;
    dlg->chars_shown = 0;
    handle_dialogue_end(game, lobby);
}
