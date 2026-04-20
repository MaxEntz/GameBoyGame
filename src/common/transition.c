/*
** EPITECH PROJECT, 2025
** GameBoyGame
** File description:
** transition.c
*/

#include "common/transition.h"

static const UINT8 transition_palette[TRANSITION_STEPS] = {
    0xE4, // Normal
    0xF9, // Light Gray
    0xFE, // Dark Gray
    0xFF  // Dark
};

void transition_fade_out(void)
{

    for (UINT8 step = 0; step < TRANSITION_STEPS; step++) {
        BGP_REG = transition_palette[step];
        wait_vbl_done();
        delay(TRANSITION_DELAY);
    }
    return;
}

void transition_fade_in(void)
{
    for (UINT8 step = TRANSITION_STEPS; step > 0; step--) {
        BGP_REG = transition_palette[step - 1];
        wait_vbl_done();
        delay(TRANSITION_DELAY);
    }
    return;
}

void transition_sound(void)
{
    NR50_REG = 0xFF;        // Set master volume to max
    NR51_REG = 0xFF;        // Enable all sound channels for both left and right output
    NR52_REG = 0x80;        // Turn on the sound system

    // idk, random values for beep sound
    NR10_REG=0X00;
    NR11_REG=0X81;
    NR12_REG=0X43;
    NR13_REG=0X73;
    NR14_REG=0X86;
    return;
}