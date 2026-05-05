/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** random.c
*/

#include <gb/gb.h>
#include "common/random.h"

static UINT16 g_seed;

void
random_init(UINT8 keys)
{
    g_seed = (UINT16)(DIV_REG * keys);
}

UINT8
random_get(UINT8 modulo)
{
    UINT16 temp = g_seed * DIV_REG;

    return (UINT8)(temp % modulo);
}
