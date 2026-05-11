/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** random.h
*/

#ifndef RANDOM_H_
    #define RANDOM_H_

    #include "common/project_types.h"

/**
 * @brief Seed the RNG from the DIV register (call when player starts a game)
 */
void
random_init(UINT8 keys);

/**
 * @brief Return a pseudo-random number in [0, modulo]
 *
 * @param modulo maximum value for the random number
 * @return UINT8 Random value
 */
UINT8
random_get(UINT8 modulo);

#endif /* !RANDOM_H_ */
