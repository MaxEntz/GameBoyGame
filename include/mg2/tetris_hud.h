/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris_hud.h
*/

#ifndef TETRIS_HUD_H_
    #define TETRIS_HUD_H_

    #include "common/project_types.h"

/**
 * @brief Draw the current score
 * 
 * @param score score value to display
 */
void
draw_score(INT16 score);

/**
 * @brief Draw the cleared lines counter
 * 
 * @param lines number of cleared lines to display
 */
void
draw_lines(UINT8 lines);

/**
 * @brief Draw the current level
 * 
 * @param level level number to display
 */
void
draw_level(UINT8 level);

/**
 * @brief Draw the entire HUD (labels + values)
 * 
 * @param score current score
 * @param level current level
 * @param lines total cleared lines
 */
void
draw_hud(INT16 score, UINT8 level, UINT8 lines);

#endif /* !TETRIS_HUD_H_ */
