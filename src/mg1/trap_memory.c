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

    g_tm.player_x = 88;
    g_tm.player_y = 78;
    g_tm.is_moving = FALSE;
    g_tm.moving_dir = MOVING_SENS_DOWN;
    g_tm.fps_counter = 0;

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
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    HIDE_WIN;
    text_renderer_init();
}

trap_memory_t
*trap_memory_get(void)
{
    return &g_tm;
}

void
update_trap_memory(OUT game_t *game)
{
    (void)game;
    g_tm.fps_counter++;
    if (g_tm.fps_counter >= 60) {
        g_tm.fps_counter = 0;
    }
    move_sprite_personage(&g_tm);
    move_sprite(0, g_tm.player_x, g_tm.player_y);
    move_sprite(1, g_tm.player_x + 8, g_tm.player_y);
    move_sprite(2, g_tm.player_x, g_tm.player_y + 8);
    move_sprite(3, g_tm.player_x + 8, g_tm.player_y + 8);
}
