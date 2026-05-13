/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** dialogue.h
*/

#ifndef DIALOGUE_H_
    #define DIALOGUE_H_

    #include "common/common.h"
    #include "common/asset_dialogue.h"

    #define DIALOGUE_WIN_Y        112   // Pixel row 18 - 4 = bottom 4 rows
    #define DIALOGUE_INNER_W      18    // Interior width in tiles (20 - 2 borders)
    #define DIALOGUE_LETTER_DELAY 5     // Frames between each revealed letter

/**
 * @brief Dialogue animation states
 */
typedef enum {
    DIALOGUE_STATE_INACTIVE,
    DIALOGUE_STATE_ANIMATING,
    DIALOGUE_STATE_WAITING
} dialogue_state_t;

/**
 * @brief Dialogue runtime state
 *
 * Zero-initialize this struct before first use (DIALOGUE_STATE_INACTIVE == 0).
 * You can use '\\n' to separate lines; each page shows at most 2 lines.
 * 
 * @param text         Full dialogue text pointer
 * @param state        Current animation state
 * @param page         Current page index
 * @param chars_shown  Number of characters currently shown
 * @param timer        Frames until next character reveal (when animating)
 * @param total_chars  Total characters on current page (for animation)
 */
typedef struct dialogue_s {
    const CHAR       *text;
    dialogue_state_t  state;
    UINT8             page;
    UINT8             chars_shown;
    UINT8             timer;
    UINT8             total_chars;
    BOOLEAN           key_up;
} dialogue_t;

/**
 * @brief Load dialogue box tiles into VRAM - call once at startup
 */
void
dialogue_init(void);

/**
 * @brief Allow dialogue_init to reload tiles (call before vram_clear)
 */
void
dialogue_destroy(void);

/**
 * @brief Open the dialogue box and begin rendering the given text
 * 
 * Too long lines arent displayed fully, sorryyyyyy
 *
 * @param dlg  Dialogue state to initialise
 * @param text Null-terminated string; '\n' separates lines (2 per page)
 */
void
dialogue_start(INOUT dialogue_t *dlg, IN const CHAR *text);

/**
 * @brief Advance the letter-by-letter animation - call every frame
 *
 * @param dlg Dialogue state
 */
void
dialogue_update(INOUT dialogue_t *dlg);

/**
 * @brief Handle A/B input: skip animation, next page, or close
 *
 * @param dlg  Dialogue state
 * @param keys Current joypad() result
 */
void
dialogue_handle_input(INOUT dialogue_t *dlg, IN UINT8 keys);

/**
 * @brief Returns TRUE while the dialogue box is visible
 *
 * @param dlg Dialogue state
 */
BOOLEAN
dialogue_is_active(IN const dialogue_t *dlg);

#endif /* !DIALOGUE_H_ */
