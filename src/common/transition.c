/*
** EPITECH PROJECT, 2025
** GameBoyGame
** File description:
** transition.c
*/

#include "common/transition.h"

void transition_effect(void)
{
    return;
}

void transition_sound(void)
{
    NR50_REG = 0xFF;
    NR51_REG = 0xFF;
    NR52_REG = 0x80;
    NR10_REG = 0x38U;
    NR11_REG = 0x70U;
    NR12_REG = 0xE0U;
    NR13_REG = 0x0AU;
    NR14_REG = 0xC6U;

    NR51_REG |= 0x11;
    
    delay(200);
    return;
}