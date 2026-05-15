/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** trap_memory.c
*/

#include "mg1/trap_memory.h"

static trap_memory_t g_tm;
static const UINT8 g_tm_map[COMMON_SCREEN_WIDTH_TILES * COMMON_SCREEN_HEIGHT_TILES] = {
    6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,6 ,7 ,
    8 ,9 ,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,8 ,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
    8 ,13,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,12,9 ,
    6 ,13,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,12,7 ,
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

static CHAR g_tm_score_text[] = "SCORE 00000";
static CHAR g_tm_level_text[] = "LEVEL 01";
static CHAR g_tm_gameover_text[] = "GAME OVER";
static CHAR g_tm_victory_text[] = "VICTORY !";

static const text_render_t g_tm_score_render = {g_tm_score_text, 1, 0};
static const text_render_t g_tm_level_render = {g_tm_level_text, 11, 0};
static const text_render_t g_tm_gameover_render = {g_tm_gameover_text, 5, 9};
static const text_render_t g_tm_victory_render = {g_tm_victory_text, 5, 9};

/**
 * @brief Write a number into a string with leading zeros
 * @param dst The destination string (must have enough space for the digits)
 * @param digits The number of digits to write (leading zeros will be added if necessary)
 * @param value The number to write
 * @return void
 */
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

/**
 * @brief Draw the heads-up display (HUD)
 * @param game The game instance
 * @return void
 */
static void
tm_draw_hud(IN const game_t *game)
{
    UINT16 score = game->score_mg1;

    if (g_tm.hud_ready && g_tm.last_score == (UINT16)score
        && g_tm.last_level == game->level)
        return;
    tm_write_number(&g_tm_score_text[6], 3, score);
    tm_write_number(&g_tm_level_text[6], 2, game->level);
    text_renderer_draw(&g_tm_score_render);
    text_renderer_draw(&g_tm_level_render);
    g_tm.last_score = (UINT16)score;
    g_tm.last_level = game->level;
    g_tm.hud_ready = TRUE;
}

/**
 * @brief Initialize the trap memory structure
 * @return void
 */
static void
init_tm_struct(void)
{
    g_tm.player_x = 88;
    g_tm.player_y = 78;
    g_tm.is_moving = FALSE;
    g_tm.moving_dir = MOVING_SENS_DOWN;
    g_tm.fps_counter = 0;
    g_tm.seconds_counter = 0;
    g_tm.time_round = ROUND_TIME - 1;
    g_tm.nb_round = 0;
    g_tm.nb_safe_tiles = MAX_SAFE_TILES;
    g_tm.hud_ready = FALSE;
    g_tm.last_score = 0;
    g_tm.last_level = 1;
    g_tm.see_safe_tile = TIME_SEE_SAFE_TILE;
    g_tm.total_time_round = ROUND_TIME;
    g_tm.game_finished = FALSE;
    g_tm.block_movement = FALSE;
    for (UINT16 i = 0; i < COMMON_SCREEN_WIDTH_TILES * COMMON_SCREEN_HEIGHT_TILES; i++)
        g_tm.current_map[i] = g_tm_map[i];
} 

void
trap_memory(OUT game_t *game)
{
    game->score_mg1 = 0;
    game->level = 1;
    
    init_tm_struct();
    SPRITES_8x8;
    set_bkg_data(0, 1, grass_tile);
    set_bkg_data(1, 1, void_tile);
    set_bkg_data(2, 4, tronc_tile);
    set_bkg_data(6, 4, wall_tile);
    set_bkg_data(10, 4, wall_tile_limit);
    set_bkg_data(14, 1, wall_crossing_tile);
    set_bkg_data(15, 4, bush_tile);
    set_bkg_data(19, 4, flower_tile);
    set_bkg_data(0 + OFFSET_SAFER_TILE, 1, safe_tile_void);
    set_bkg_data(1 + OFFSET_SAFER_TILE, 1, safe_tile_grass);
    set_bkg_tiles(0, 0, 20, 18, g_tm_map);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    HIDE_WIN;
    text_renderer_init();
    tm_draw_hud(game);
}

trap_memory_t
*trap_memory_get(void)
{
    return &g_tm;
}

/**
 * @brief Find a new safe tile position
 * @param map The map array
 * @return void
 */
static void
find_new_safe_tile(OUT UINT8 *map)
{
    UINT16 index_x = 0;
    UINT16 index_y = 0;
    UINT8 tile = 0;

    for (INT16 i = 0; i < (INT16)g_tm.nb_safe_tiles; i++) {
        index_x = (UINT16)(random_get(COMMON_SCREEN_WIDTH_TILES - 4)) + 1;
        index_y = (UINT16)(random_get(COMMON_SCREEN_HEIGHT_TILES - 4)) + 1;
        g_tm.hitbox_safe_tile[i][0] = index_x;
        g_tm.hitbox_safe_tile[i][1] = index_y;
        tile = map[index_y * COMMON_SCREEN_WIDTH_TILES + index_x];
        if (tile == 0) {
            map[index_y * COMMON_SCREEN_WIDTH_TILES + index_x] = 1 + OFFSET_SAFER_TILE;
            map[index_y * COMMON_SCREEN_WIDTH_TILES + index_x + 1] = 0 + OFFSET_SAFER_TILE;
            map[(index_y + 1) * COMMON_SCREEN_WIDTH_TILES + index_x] = 0 + OFFSET_SAFER_TILE;
            map[(index_y + 1) * COMMON_SCREEN_WIDTH_TILES + index_x + 1] = 1 + OFFSET_SAFER_TILE;
        } else if (tile == 1) {
            map[index_y * COMMON_SCREEN_WIDTH_TILES + index_x] = 0 + OFFSET_SAFER_TILE;
            map[index_y * COMMON_SCREEN_WIDTH_TILES + index_x + 1] = 1 + OFFSET_SAFER_TILE;
            map[(index_y + 1) * COMMON_SCREEN_WIDTH_TILES + index_x] = 1 + OFFSET_SAFER_TILE;
            map[(index_y + 1) * COMMON_SCREEN_WIDTH_TILES + index_x + 1] = 0 + OFFSET_SAFER_TILE;
        } else
            i--;
    }

    return;
}

/**
 * @brief Clear the map
 * @param map The map array
 * @return void
 */
static void
clear_map(OUT UINT8 *map)
{
    for (UINT16 i = 0; i < COMMON_SCREEN_WIDTH_TILES * COMMON_SCREEN_HEIGHT_TILES; i++) {
        map[i] = g_tm_map[i];
    }
}

/**
 * @brief Check if the player is colliding with a wall in the given direction
 * @param game Pointer to the game structure
 * @param sens The direction of movement (left, right, up, down)
 * @return TRUE if colliding with a wall, FALSE otherwise
 */
static BOOLEAN
check_game_over(IN const game_t *game)
{
    INT16 bg_x = (INT16)g_tm.player_x - 8;
    INT16 bg_y = (INT16)g_tm.player_y - 16;
    UINT8 pos_x = (UINT8)(bg_x >> 3);
    UINT8 pos_y = (UINT8)(bg_y >> 3);

    if (game->score_mg1 == 0)
        return FALSE;
    for (UINT8 i = 0; i < g_tm.nb_safe_tiles; i++) {
        if (pos_x + 1 >= g_tm.hitbox_safe_tile[i][0] && pos_x - 1 <= g_tm.hitbox_safe_tile[i][0] + 2
            && pos_y + 1 >= g_tm.hitbox_safe_tile[i][1] && pos_y - 1 <= g_tm.hitbox_safe_tile[i][1] + 2)
            return FALSE;
    }
    text_renderer_draw(&g_tm_gameover_render);
    g_tm.game_finished = TRUE;
    g_tm.time_round = g_tm.see_safe_tile + 1;
    g_tm.total_time_round = g_tm.see_safe_tile + 3;
    return TRUE;
}

/**
 * @brief Handle the logic for a new round
 * @param game The game instance
 * @return void
 */
static void
handle_new_round(OUT game_t *game)
{
    if (g_tm.time_round >= g_tm.total_time_round) {
        if (g_tm.game_finished)
            return game_changer(game, GAME_STATE_LOBBY, TRUE);
        if (check_game_over(game))
            return;
        if (g_tm.nb_round == 5) {
            g_tm.nb_round = 0;
            g_tm.total_time_round -= 1;
            game->level++;
            if (game->level / 2 == 0)
                g_tm.nb_safe_tiles = (g_tm.nb_safe_tiles == 1) ? 1 : g_tm.nb_safe_tiles - 1;
        }
        g_tm.time_round = 0;
        g_tm.block_movement = TRUE;
        clear_map(g_tm.current_map);
        find_new_safe_tile(g_tm.current_map);
        set_bkg_tiles(0, 0, 20, 18, g_tm.current_map);
        game->score_mg1 += 10 * game->level;
        g_tm.nb_round++;
        tm_draw_hud(game);
    }
    if (g_tm.time_round == g_tm.see_safe_tile && g_tm.fps_counter == 0) {
        clear_map(g_tm.current_map);
        set_bkg_tiles(0, 0, 20, 18, g_tm.current_map);
        g_tm.hud_ready = FALSE;
        g_tm.block_movement = FALSE;
        tm_draw_hud(game);
    }
}

void
update_trap_memory(OUT game_t *game)
{
    tm_draw_hud(game);
    g_tm.fps_counter++;
    if (g_tm.fps_counter >= 60) {
        g_tm.fps_counter = 0;
        g_tm.seconds_counter++;
        g_tm.time_round++;
    }
    handle_new_round(game);
    move_sprite_personage(&g_tm);
    move_sprite(0, g_tm.player_x, g_tm.player_y);
    move_sprite(1, g_tm.player_x + 8, g_tm.player_y);
    move_sprite(2, g_tm.player_x, g_tm.player_y + 8);
    move_sprite(3, g_tm.player_x + 8, g_tm.player_y + 8);
}
