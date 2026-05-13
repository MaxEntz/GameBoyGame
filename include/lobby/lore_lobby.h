/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lore_lobby.h
*/

#ifndef LORE_LOBBY_H_
    #define LORE_LOBBY_H_

    #include "common/common.h"

typedef enum lore_step_e {
    LORE_LEFT_INTRO  = 0,
    LORE_LEFT_LOSE   = 1,
    LORE_LEFT_WIN    = 2,
    LORE_RIGHT_INTRO = 3,
    LORE_RIGHT_LOSE  = 4,
    LORE_RIGHT_WIN   = 5,
    LORE_CC_INTRO    = 6,
    LORE_CC_LOSE     = 7,
    LORE_CC_WIN      = 8,
    LORE_STEP_COUNT  = 9
} lore_step_t;

/**
 * @brief Start the dialogue when the player interacts with an NPC.
 * 
 * @param game Pointer to the game structure
 */
void
lore_start_dialogue(OUT game_t *game);

/**
 * @brief Advance dialogue animation and handle transitions.
 * Call every frame while in the lobby.
 * @param game Pointer to the game structure
 */
void
lore_update(OUT game_t *game);

#endif /* !LORE_LOBBY_H_ */
