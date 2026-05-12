/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lore_lobby.h
*/

#ifndef LORE_LOBBY_H_
    #define LORE_LOBBY_H_

    #include "common/common.h"

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
