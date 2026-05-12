/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** random.c
*/

#include <gb/gb.h>
#include "common/random.h"
#include <rand.h>

static UINT16 g_seed;

void
random_init(UINT8 keys)
{
    g_seed = (UINT16)(DIV_REG * keys);
    initrand(g_seed);
}

UINT8
random_get(UINT8 modulo)
{
    UINT16 temp = rand();

    return (UINT8)(temp % modulo);
}
