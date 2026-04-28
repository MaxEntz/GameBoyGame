/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** flappy.h
*/

#ifndef FLAPPY_H_
    #define FLAPPY_H_

    #include "common/common.h"
    #include "common/game_changer.h"

/**
 * @brief Load the Flappy Bird assets and handle its state
 * @param game Pointer to the game structure
 * @return void
 */
void
flappybird(OUT game_t *game);

/**
 * @brief Update of Flappy Bird
 * @param game Pointer to the game structure
 * @return void
 */
void
update_flappybird(OUT game_t *game);

/**
 * @brief Handle the input handle of Flappy Bird
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_flappybird(OUT game_t *game, 
                        IN UINT8 keys);

#endif /* FLAPPY_H_ */
