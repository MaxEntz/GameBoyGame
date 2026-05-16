/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** save_select.c
*/

#include "menu/save_select.h"

static text_render_t g_continue_render = {"CONTINUE", 6, 8};
static text_render_t g_new_render = {"NEW SAVE", 6, 10};
static text_render_t g_cursor_render = {"!", 4, 8};
static BOOLEAN g_has_save = FALSE;
static UINT8 g_selected = 0;

void
save_select(OUT game_t *game)
{
    (void)game;
    set_bkg_data(0, 1, void_tile);
    set_bkg_tiles(0, 0, 20, 18, save_select_map);
    text_renderer_init();
    {
        save_data_t tmp;

        ENABLE_RAM;
        memcpy(&tmp, (const void *)SRAM_BASE, sizeof(save_data_t));
        DISABLE_RAM;
        if (tmp.magic == SAVE_MAGIC) {
            g_has_save = TRUE;
            g_selected = 0;
        } else {
            g_has_save = FALSE;
            g_selected = 1;
        }
    }

    text_renderer_draw(&g_continue_render);
    text_renderer_draw(&g_new_render);
    g_cursor_render.y = g_selected == 0 ? g_continue_render.y : g_new_render.y;
    text_renderer_draw(&g_cursor_render);
}

void
handle_input_save_select(OUT game_t *game,
                        IN UINT8 keys)
{   
    UINT8 prev = g_selected;

    if (keys & J_UP) {
        if (g_has_save)
            g_selected = 0;
        else
            g_selected = 1;
    }
    if (keys & J_DOWN) {
        g_selected = 1;
    }

    if (prev != g_selected) {
        text_render_t old_cursor = {g_cursor_render.text, g_cursor_render.x, g_cursor_render.y};

        text_renderer_clear(&old_cursor);
        g_cursor_render.y = g_selected == 0 ? g_continue_render.y : g_new_render.y;
        text_renderer_draw(&g_cursor_render);
    }

    if (keys & (J_A)) {
        if (g_selected == 0 && g_has_save) {
            save_load(game);
            game_changer(game, GAME_STATE_LOBBY, TRUE);
        } else if (g_selected == 1) {
            save_reset(game);
            game_changer(game, GAME_STATE_CHOOSE_DIFFICULTY, TRUE);
        }
    }
}

void
update_save_select(OUT game_t *game)
{
    (void)game;
}
