/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** text_renderer.c
*/

#include <gb/gb.h>

#include "common/text_renderer.h"
#include "common/asset_common_font.h"

static BOOLEAN g_text_renderer_ready = FALSE;

/**
 * @brief Convert a character to its corresponding font tile index
 * 
 * @param c The character to convert
 * @return The tile index corresponding to the character in the font tileset
 */
static UINT8
char_to_font_index(CHAR c)
{
    if (c >= 'a' && c <= 'z')
        c -= ('a' - 'A');
    if (c == ' ')
        return TILE_SPACE;
    if (c >= 'A' && c <= 'Z')
        return (UINT8)(TILE_A + (c - 'A'));
    if (c >= '0' && c <= '9')
        return (UINT8)(TILE_0 + (c - '0'));
    return 0;
}

void
text_renderer_init(void)
{
    if (g_text_renderer_ready)
        return;
    set_bkg_data(COMMON_FONT_BASE_TILE,
                 (UINT8)TILE_COUNT,
                 common_font_tiles);
    g_text_renderer_ready = TRUE;
}

void
text_renderer_draw(OUT const text_render_t *render)
{
    UINT8 index = 0;

    if (render == NULL || render->text == NULL)
        return;
    while (render->text[index] != '\0'
        && (UINT8)(render->x + index) < COMMON_SCREEN_WIDTH_TILES) {
        set_bkg_tile_xy((UINT8)(render->x + index),
                        render->y,
                        (UINT8)(COMMON_FONT_BASE_TILE +
                        char_to_font_index(render->text[index])));
        index++;
    }
}

void
text_renderer_clear(OUT const text_render_t *render)
{
    UINT8 index = 0;

    if (render == NULL || render->text == NULL)
        return;
    while (render->text[index] != '\0'
        && (UINT8)(render->x + index) < COMMON_SCREEN_WIDTH_TILES) {
        set_bkg_tile_xy((UINT8)(render->x + index),
                        render->y,
                        TILE_SPACE);
        index++;
    }
}
