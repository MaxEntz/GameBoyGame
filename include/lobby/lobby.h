/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lobby.h
*/

#ifndef LOBBY_H_
    #define LOBBY_H_

    #include "asset_lobby.h"
    #include "common/common.h"

/**
 * @brief Load the lobby assets and handle the lobby state
 * We can see it like a creator in CPP
 * @param game Pointer to the game structure
 * @return void
 */
void
lobby(OUT game_t *game);

/**
 * @brief Handle the input in the lobby state
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_lobby(OUT game_t *game,
                   IN UINT8 keys);

/**
 * @brief Update the lobby state
 * @param game Pointer to the game structure
 * @return void
 */
void
update_lobby(OUT game_t *game);

#endif /* !LOBBY_H_ */
