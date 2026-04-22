/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** tetris.c
*/

#include "mg2/mg2.h"
#include "common/text_renderer.h"

/**
 * @brief Load the tetris assets and handle the tetris state
 * @param game Pointer to the game structure
 * @return void
 */
static void
load_assets(void)
{
    set_bkg_data(0, 1, grass_tile);
    set_bkg_data(1, 1, wall_tile);
    set_bkg_tiles(0, 0, 20, 18, map);
    set_sprite_data(0, 1, square_tile);
    set_sprite_tile(0, 0);
}

void
tetris(OUT game_t *game)
{
    (void)game;
    load_assets();
}

void
update_tetris(OUT game_t *game)
{
    move_sprite(0, game->player_x, game->player_y);
}

void
handle_input_tetris(OUT game_t *game,
                   IN UINT8 keys)
{
    text_render_t test = {
        .text = "ZebI",
        .x = (COMMON_SCREEN_WIDTH_TILES - 7) / 2,
        .y = COMMON_SCREEN_HEIGHT_TILES / 2
    };

    if (keys & J_A)
        text_renderer_clear(&test);
    if (keys & J_B) {
        text_renderer_draw(&test);
    }

    if (keys & J_LEFT && game->player_x > 8 + 16)
        game->player_x += SPEED;
    if (keys & J_RIGHT && game->player_x < 168 - 16)
        game->player_x -= SPEED;
    if (keys & J_UP && game->player_y > 8 + 16)
        game->player_y += SPEED;
    if (keys & J_DOWN && game->player_y < 144 - 16)
        game->player_y -= SPEED;
}
