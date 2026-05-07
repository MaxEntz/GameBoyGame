/*
** EPITECH PROJECT, 2026
** vram_clear.h
** File description:
** 
**/

#ifndef VRAM_CLEAR_H_
    #define VRAM_CLEAR_H_

#include "common/common.h"
#include "common/text_renderer.h"

/**
 * @brief Zero all 256 bg tile slots, clear the tilemap and hide all sprites
 */
 void
vram_clear(void);

#endif /* !VRAM_CLEAR_H_ */