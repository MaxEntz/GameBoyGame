/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** menu.c
*/

#include "menu/menu.h"
#include "common/game_changer.h"
#include "common/vram_clear.h"

/**
 * @brief Draw the menu text
 */
static void
draw_text(void)
{
    static const text_render_t title = {"???? THE MOLE", 3, 9};
    static const text_render_t prompt = {"PRESS START", 4, 13};

    text_renderer_draw(&title);
    text_renderer_draw(&prompt);
}

void
menu(OUT game_t *game)
{
    (void)game;
    vram_clear();
    delay(1000);        //debug pour montrer que ca marcheeeee
    text_renderer_init();
    draw_text();
}

void
handle_input_menu(OUT game_t *game,
                  IN UINT8 keys)
{
    if (keys & J_START)
        game_changer(game, GAME_STATE_LOBBY);
}

void
update_menu(OUT game_t *game)
{
    (void)game;
}
