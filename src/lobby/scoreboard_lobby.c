/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** scoreboard_lobby.c
*/

#include "lobby/scoreboard_lobby.h"
#include "common/text_renderer.h"

/**
 * @brief Write val as a zero-padded 5-digit decimal string into buf
 */
static void
int_to_str5(INT16 val, CHAR *buf)
{
    INT8 i;
    UINT16 uval = (UINT16)val;

    for (i = 4; i >= 0; i--) {
        buf[i] = '0' + (CHAR)(uval % 10);
        uval /= 10;
    }
    buf[5] = '\0';
}

/**
 * @brief Render one score row with the label, best score and player's score
 */
static void
draw_score_row(IN const CHAR *label, IN INT16 best, IN INT16 you, IN UINT8 y)
{
    CHAR          buf[6];
    text_render_t render = {label, 2, y};

    text_renderer_draw(&render);
    int_to_str5(best, buf);
    render.text = buf;
    render.x = 7;
    text_renderer_draw(&render);
    int_to_str5(you, buf);
    render.x = 13;
    text_renderer_draw(&render);
}

void
draw_scoreboard(IN game_t *game)
{
    static const text_render_t g_headers[] = {
        {"SCOREBOARD", 5,  2},
        {"BEST",       7,  6},
        {"YOU",       14,  6},
        {NULL,         0,  0}
    };
    UINT8 i = 0;

    while (g_headers[i].text != NULL)
        text_renderer_draw(&g_headers[i++]);
    draw_score_row("TETR", game->best_score_mg2, game->score_mg2, 8);
    draw_score_row("FLAP", game->best_score_mg3, game->score_mg3, 10);
    draw_score_row("TRAP",   game->best_score_mg1, game->score_mg1, 12);
}
