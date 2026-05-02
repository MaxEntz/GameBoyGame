/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_hud.h
*/

#ifndef TETRIS_HUD_H_
    #define TETRIS_HUD_H_

    #include "common/project_types.h"

void
draw_score(INT16 score);

void
draw_lines(UINT8 lines);

void
draw_level(UINT8 level);

void
draw_hud(INT16 score, UINT8 level, UINT8 lines);

#endif /* !TETRIS_HUD_H_ */
