/*
** EPITECH PROJECT, 2025
** GameBoyGame
** File description:
** mg2.h
*/

#ifndef MG2_H
#define MG2_H

#include "common/common.h"
#include "common/game_changer.h"

#include "asset_lobby.h"    //a enlever

/**
 * @brief Load the lobby assets and handle the tetris state
 * We can see it like a creator in CPP
 * @param game Pointer to the game structure
 * @return void
 */
void
tetris(OUT game_t *game);

/**
 * @brief Handle the input in the tetris state
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_tetris(OUT game_t *game,
                   IN UINT8 keys);

/**
 * @brief Update the tetris state
 * @param game Pointer to the game structure
 * @return void
 */
void
update_tetris(OUT game_t *game);
#endif /* MG2_H */