/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** text_renderer.h
*/

#ifndef TEXT_RENDERER_H_
    #define TEXT_RENDERER_H_

    #include "common/common.h"

    #define COMMON_FONT_BASE_TILE 128U      //où on load les tiles dans la VRAM

/**
 * @brief Structure to represent a text to render on the background
 * 
 * @param text The text to render, must be null-terminated
 * @param x The x position in tiles (0-19)
 * @param y The y position in tiles (0-17)
 */
typedef struct text_render_s {
    const CHAR *text;
    UINT8       x;
    UINT8       y;
} text_render_t;

/**
 * @brief Initialize the text renderer by loading the font tiles into VRAM
 * This function must be called before any call to text_renderer_draw
 */
void
text_renderer_init(void);

/**
 * @brief Destroy the text renderer, allowing it to be re-initialized if needed
 */
void
text_renderer_destroy(void);

/**
 * @brief Draw the given text on the background layer
 * 
 * @param render The text render configuration, including the text and its position
 * The text must be null-terminated and can only contain characters A-Z, a-z,
 */
void
text_renderer_draw(OUT const text_render_t *render);

/**
 * @brief Clear the text drawn by text_renderer_draw
 * 
 * @param render The text render configuration, including the text and its position
 */
void
text_renderer_clear(OUT const text_render_t *render);

#endif /* !TEXT_RENDERER_H_ */