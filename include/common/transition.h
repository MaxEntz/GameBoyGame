/*
** EPITECH PROJECT, 2025
** GameBoyGame
** File description:
** transition.h
*/

#ifndef TRANSITION_H
#define TRANSITION_H

#define TRANSITION_STEPS 4
#define TRANSITION_DELAY 100

#include "common/common.h"


/**
 * @brief Play a visual effect for the transition
 * 
 * Fades the pixels to darkest of 4 levels of darkness
 */
void transition_fade_out(void);


/**
 * @brief Play a visual effect for the transition
 * 
 * Fades the pixels from the darkest of 4 levels of darkness to normal
 */
void transition_fade_in(void);

/**
 * @brief Play a sound effect for the transition
 * 
 * This function will play a sound effect for the transition between game states.
 */
void transition_sound(void);

#endif /* TRANSITION_H */