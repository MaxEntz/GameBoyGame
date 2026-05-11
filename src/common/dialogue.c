/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** dialogue.c
*/

#include <gb/gb.h>

#include "common/dialogue.h"
#include "common/text_renderer.h"
#include "common/asset_common_font.h"

static BOOLEAN g_dialogue_ready = FALSE;

/**
 * @brief Map a character to its VRAM tile index in the font
 * 
 * @param c Character to map
 * @return UINT8 Tile index for the given character, or space tile for unsupported chars
 */
static UINT8
char_to_tile(CHAR c)
{
    if (c >= 'a' && c <= 'z')
        c -= ('a' - 'A');
    if (c == ' ')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_SPACE);
    if (c >= 'A' && c <= 'Z')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_A + (c - 'A'));
    if (c >= '0' && c <= '9')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_0 + (c - '0'));
    if (c == '.')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_PERIOD);
    if (c == ',')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_COMMA);
    if (c == '!')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_EXCL);
    if (c == '?')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_QUEST);
    if (c == '\'')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_APOS);
    if (c == '-')
        return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_HYPHEN);
    return (UINT8)(COMMON_FONT_BASE_TILE + FTILE_SPACE);
}

/**
 * @brief Return the length of line N in text (capped at DIALOGUE_INNER_W)
 * and fill *start_offset with its byte offset (may be NULL)
 * 
 * @param text Full dialogue text
 * @param line_num The number of the line to measure (and to go to)
 * @param start_offset The byte offset of the start of the line within text
 * @return UINT8 Length of the line in characters, capped at DIALOGUE_INNER
 */
static UINT8
get_line_info(IN const CHAR *text, IN UINT8 line_num, OUT UINT8 *start_offset)
{
    UINT8 pos = 0;
    UINT8 cur = 0;
    UINT8 len = 0;

    while (cur < line_num) {
        if (text[pos] == '\0')
            return 0;
        if (text[pos] == '\n')
            cur++;
        pos++;
    }
    if (start_offset != NULL)
        *start_offset = pos;
    while (text[pos + len] != '\0' && text[pos + len] != '\n'
           && len < DIALOGUE_INNER_W)
        len++;
    return len;
}

/**
 * @brief Total visible characters on page (line N*2 + line N*2+1)
 * 
 * @param text Full dialogue text
 * @param page Page number to measure
 * @return UINT8 Total characters on the page, capped at 2 * DIALOGUE_INNER_W
 */
static UINT8
compute_page_chars(IN const CHAR *text, IN UINT8 page)
{
    UINT8 len1 = get_line_info(text, (UINT8)(page * 2), NULL);
    UINT8 len2 = get_line_info(text, (UINT8)(page * 2 + 1), NULL);

    return (UINT8)(len1 + len2);
}

/**
 * @brief Returns TRUE if a page after the current one exists
 * 
 * @param text Full dialogue text
 * @param page Current page number
 * @return BOOLEAN TRUE if there is another page after the current one, FALSE otherwise
 */
static BOOLEAN
has_next_page(IN const CHAR *text, IN UINT8 page)
{
    return get_line_info(text, (UINT8)((page + 1) * 2), NULL) > 0;
}

/**
 * @brief Play a short sound for text typing (horrible)
 */
static void
play_type_sound(void)
{
    NR50_REG = 0xFF;        // Set master volume to max
    NR51_REG = 0xFF;        // Enable all sound channels for both left and right output
    NR52_REG = 0x80;        // Turn on the sound system

    NR10_REG = 0x00;
    NR11_REG = 0x81;
    NR12_REG = 0x43;        
    NR13_REG = 0x90;
    NR14_REG = 0x86;
}

/**
 * @brief Place the tile for the next character and return that character
 * 
 * @param dlg Dialogue state containing the text and current page
 * @param chars_shown Number of characters currently shown (including the one to draw)
 * @return CHAR The character that was drawn, or space if out of bounds
 */
static CHAR
draw_char_at(IN dialogue_t *dlg, IN UINT8 chars_shown)
{
    UINT8 line1_off;
    UINT8 line2_off;
    UINT8 line1_len;
    UINT8 line2_len;
    UINT8 idx;
    UINT8 x;
    CHAR  c;

    line1_len = get_line_info(dlg->text, (UINT8)(dlg->page * 2), &line1_off);
    line2_len = get_line_info(dlg->text, (UINT8)(dlg->page * 2 + 1), &line2_off);
    if (chars_shown <= line1_len) {
        idx = (UINT8)(chars_shown - 1);
        x   = (UINT8)(1U + (DIALOGUE_INNER_W - line1_len) / 2 + idx);
        c   = dlg->text[line1_off + idx];
    } else {
        idx = (UINT8)(chars_shown - line1_len - 1U);
        x   = (UINT8)(1U + (DIALOGUE_INNER_W - line2_len) / 2 + idx);
        c   = dlg->text[line2_off + idx];
    }
    set_win_tile_xy(x, (UINT8)(chars_shown <= line1_len ? 1 : 2), char_to_tile(c));
    return c;
}


/**
 * @brief Instantly finish the animation for the current page, showing all remaining characters
 * and transition to the waiting state
 * 
 * @param dlg Dialogue state to skip animation for
 */
static void
skip_animation(INOUT dialogue_t *dlg)
{
    while (dlg->chars_shown < dlg->total_chars) {
        dlg->chars_shown++;
        draw_char_at(dlg, dlg->chars_shown);
    }
    dlg->state = DIALOGUE_STATE_WAITING;
}

/**
 * @brief Advance to the next page of dialogue, or close if there are no more pages
 * 
 * @param dlg Dialogue state to advance
 */
static void
advance_page(INOUT dialogue_t *dlg)
{
    dlg->page++;
    dlg->chars_shown = 0;
    dlg->timer       = 0;
    dlg->total_chars = compute_page_chars(dlg->text, dlg->page);
    set_win_tiles(0, 0, 20, 4, dialogue_box_map);
    dlg->state = DIALOGUE_STATE_ANIMATING;
}

/**
 * @brief Close the dialogue box and reset state
 * 
 * @param dlg Dialogue state to reset
 */
static void
close_dialogue(INOUT dialogue_t *dlg)
{
    HIDE_WIN;
    dlg->state = DIALOGUE_STATE_INACTIVE;
}


void
dialogue_init(void)
{
    if (g_dialogue_ready)
        return;
    set_bkg_data(DIALOGUE_TILE_BASE, (UINT8)DTILE_COUNT, dialogue_box_tiles);
    g_dialogue_ready = TRUE;
}

void
dialogue_destroy(void)
{
    g_dialogue_ready = FALSE;
}

void
dialogue_start(INOUT dialogue_t *dlg, IN const CHAR *text)
{
    dlg->text        = text;
    dlg->page        = 0;
    dlg->chars_shown = 0;
    dlg->timer       = 0;
    dlg->total_chars = compute_page_chars(text, 0);
    dlg->key_up      = FALSE;
    dlg->state       = DIALOGUE_STATE_ANIMATING;
    set_win_tiles(0, 0, 20, 4, dialogue_box_map);
    move_win(MINWNDPOSX, DIALOGUE_WIN_Y);
    SHOW_WIN;
}

void
dialogue_update(INOUT dialogue_t *dlg)
{
    if (dlg->state != DIALOGUE_STATE_ANIMATING)
        return;
    if (dlg->timer > 0) {
        dlg->timer--;
        return;
    }
    dlg->chars_shown++;
    if (draw_char_at(dlg, dlg->chars_shown) != ' ')
        play_type_sound();
    dlg->timer = DIALOGUE_LETTER_DELAY;
    if (dlg->chars_shown >= dlg->total_chars)
        dlg->state = DIALOGUE_STATE_WAITING;
}

void
dialogue_handle_input(INOUT dialogue_t *dlg, IN UINT8 keys)
{
    if (dlg->state == DIALOGUE_STATE_INACTIVE)
        return;
    if (!(keys & (J_A | J_B))) {
        dlg->key_up = TRUE;
        return;
    }
    if (!dlg->key_up)
        return;
    dlg->key_up = FALSE;
    if (dlg->state == DIALOGUE_STATE_ANIMATING) {
        skip_animation(dlg);
        return;
    }
    if (has_next_page(dlg->text, dlg->page))
        advance_page(dlg);
    else
        close_dialogue(dlg);
}

BOOLEAN
dialogue_is_active(IN const dialogue_t *dlg)
{
    return dlg->state != DIALOGUE_STATE_INACTIVE;
}
