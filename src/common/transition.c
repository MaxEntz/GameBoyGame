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

static const UINT8 tone_nr13[TRANSITION_STEPS] = {0x30, 0x50, 0x70, 0x90};

void transition_fade_out(void)
{

    for (UINT8 step = 0; step < TRANSITION_STEPS; step++) {
        BGP_REG = transition_palette[step];
        wait_vbl_done();
        transition_sound(step);
        delay(TRANSITION_DELAY);
    }
    return;
}

void transition_fade_in(void)
{
    for (UINT8 step = TRANSITION_STEPS; step > 0; step--) {
        BGP_REG = transition_palette[step - 1];
        wait_vbl_done();
        transition_sound(step - 1);
        delay(TRANSITION_DELAY);
    }
    return;
}

void transition_sound(int stage)
{
    if (stage < 0 || stage >= TRANSITION_STEPS)
        stage = 0;
    NR50_REG = 0xFF;        // Set master volume to max
    NR51_REG = 0xFF;        // Enable all sound channels for both left and right output
    NR52_REG = 0x80;        // Turn on the sound system

    NR10_REG = 0x00;
    NR11_REG = 0x81;
    NR12_REG = 0x43;        
    NR13_REG = tone_nr13[stage];
    NR14_REG = 0x86;
    return;
}
