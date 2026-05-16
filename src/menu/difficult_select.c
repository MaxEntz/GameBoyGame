/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** difficult_select.c
*/

#include "menu/save_select.h"

extern BOOLEAN g_in_choose_difficulty;

static text_render_t g_difficulty_render = {"DIFFICULTY", 6, 4};
static text_render_t g_easy_render = {"EASY", 6, 8};
static text_render_t g_medium_render = {"MEDIUM", 6, 10};
static text_render_t g_hard_render = {"HARD", 6, 12};
static text_render_t g_cursor_render = {"!", 4, 8};
static UINT8 g_selected_difficulty = DIFFICULTY_EASY;
static BOOLEAN g_wait_release = FALSE;
static UINT8 g_last_keys = 0;

static void
write_selected_difficulty(game_t *game)
{
    save_data_t save;

    ENABLE_RAM;
    memcpy(&save, (const void *)SRAM_BASE, sizeof(save_data_t));
    DISABLE_RAM;
    if (save.magic != SAVE_MAGIC)
        return;
    save.difficulty = game->difficulty;
    ENABLE_RAM;
    memcpy((void *)SRAM_BASE, &save, sizeof(save_data_t));
    DISABLE_RAM;
}

void
choose_difficulty(OUT game_t *game)
{
    (void)game;
    set_bkg_data(0, 1, void_tile);
    set_bkg_tiles(0, 0, 20, 18, save_select_map);
    text_renderer_init();
    text_renderer_draw(&g_difficulty_render);
    text_renderer_draw(&g_easy_render);
    text_renderer_draw(&g_medium_render);
    text_renderer_draw(&g_hard_render);
    g_selected_difficulty = DIFFICULTY_EASY;
    g_cursor_render.y = g_easy_render.y;
    text_renderer_draw(&g_cursor_render);
    /* Ignore any lingering button press from the previous menu input */
    g_wait_release = TRUE;
    g_last_keys = 0;
}

void
handle_input_choose_difficulty(OUT game_t *game,
                               IN UINT8 keys)
{
    /* If we just entered the screen, wait until no button is pressed */
    if (g_wait_release) {
        if (keys == 0)
            g_wait_release = FALSE;
        g_last_keys = keys;
        return;
    }

    UINT8 prev = g_selected_difficulty;
    UINT8 pressed = keys & (UINT8)~g_last_keys;

    g_last_keys = keys;

    if (pressed & J_UP && g_selected_difficulty > DIFFICULTY_EASY)
        g_selected_difficulty--;
    if (pressed & J_DOWN && g_selected_difficulty < DIFFICULTY_HARD)
        g_selected_difficulty++;

    if (prev != g_selected_difficulty) {
        text_render_t old_cursor = g_cursor_render;

        text_renderer_clear(&old_cursor);
        if (g_selected_difficulty == DIFFICULTY_EASY)
            g_cursor_render.y = g_easy_render.y;
        else if (g_selected_difficulty == DIFFICULTY_MEDIUM)
            g_cursor_render.y = g_medium_render.y;
        else
            g_cursor_render.y = g_hard_render.y;
        text_renderer_draw(&g_cursor_render);
    }

    if (pressed & (J_START | J_A)) {
        game->difficulty = (difficulty_t)g_selected_difficulty;
        write_selected_difficulty(game);
        g_in_choose_difficulty = FALSE;
        game_changer(game, GAME_STATE_LOBBY, TRUE);
    }
}

void
update_choose_difficulty(OUT game_t *game)
{
    (void)game;
}
