/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** trap_memory.c
*/

#include "mg1/trap_memory.h"

static trap_memory_t g_tm;
static UINT8 g_tm_map[COMMON_SCREEN_WIDTH_TILES * COMMON_SCREEN_HEIGHT_TILES] = {
    6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,
    8 ,9 ,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,8 ,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,2 ,3 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,4 ,5 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,7 ,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,6 ,7 ,
    8 ,9 ,8 ,9 ,8 ,9 ,8 ,9 ,8 ,9 ,8 ,9 ,8 ,9 ,8 ,9 ,8 ,9 ,8 ,9 ,
};

static CHAR g_tm_score_text[] = "SCORE 000";
static CHAR g_tm_time_text[] = "TIME 00";
static CHAR g_tm_round_text[] = "ROUND 01";
static CHAR g_tm_gameover_text[] = "GAME OVER";

static const text_render_t g_tm_score_render = {g_tm_score_text, 0, 0};
static const text_render_t g_tm_time_render = {g_tm_time_text, 12, 0};
static const text_render_t g_tm_round_render = {g_tm_round_text, 0, 1};
static const text_render_t g_tm_gameover_render = {g_tm_gameover_text, 5, 9};

static void
tm_write_number(CHAR *dst, UINT8 digits, UINT16 value)
{
    UINT8 i = digits;

    while (i > 0U) {
        i--;
        dst[i] = (CHAR)('0' + (value % 10U));
        value /= 10U;
    }
}

void
trap_memory(OUT game_t *game)
{
    game->score_mg1 = 0;
    game->level = 1;

    SPRITES_8x8;
    set_bkg_data(0, 1, grass_tile);
    set_bkg_data(1, 1, void_tile);
    set_bkg_data(2, 4, tronc_tile);
    set_bkg_data(6, 4, wall_tile);
    set_bkg_data(10, 4, wall_tile_limit);
    set_bkg_data(14, 1, wall_crossing_tile);
    set_bkg_data(15, 4, bush_tile);
    set_bkg_data(19, 4, flower_tile);
    set_bkg_tiles(0, 0, 20, 18, g_tm_map);
    set_sprite_data(0, 1, square_tile);
    for (UINT8 i = 0; i < 4; i++)
        set_sprite_tile(i, 0);
    HIDE_WIN;
    text_renderer_init();
}

void
update_trap_memory(OUT game_t *game)
{

}

void
handle_input_trap_memory(OUT game_t *game,
                        IN UINT8 keys)
{

}
