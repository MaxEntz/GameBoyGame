/*
** EPITECH PROJECT, 2026
** vram_clear.c
** File description:
** 
*/

#include "common/vram_clear.h"

void
vram_clear(void)
{
    static const UINT8 blank[16] = {0};
    UINT16 i;

    for (i = 0; i < 256; i++)
        set_bkg_data((UINT8)i, 1, blank);
    text_renderer_destroy();
    dialogue_destroy();
    fill_bkg_rect(0, 0, COMMON_SCREEN_WIDTH_TILES, COMMON_SCREEN_HEIGHT_TILES, 0);
    for (i = 0; i < 40; i++)
        move_sprite((UINT8)i, 0, 0);
}