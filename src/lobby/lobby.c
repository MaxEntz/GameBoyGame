/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lobby.c
*/

#include "lobby/lobby.h"
#include "lobby/lore_lobby.h"
#include "lobby/scoreboard_lobby.h"
#include "common/text_renderer.h"
#include "common/save.h"

static lobby_state_t g_lobby;

void
lobby_init_state(void)
{
    g_lobby.inited = TRUE;
    g_lobby.fps_counter = 0;
    g_lobby.seconds_counter = 0;
    g_lobby.player_x = 88;
    g_lobby.player_y = 78;
    g_lobby.is_moving = FALSE;
    g_lobby.moving_dir = MOVING_SENS_DOWN;
    g_lobby.is_changing_map = FALSE;
    set_map(&g_lobby, MAP_ID_BL);
    g_lobby.rng_initialized = FALSE;
    g_lobby.dialogue_index = 0;
    g_lobby.should_dialogue = FALSE;
    g_lobby.is_idle_dialogue = FALSE;
    g_lobby.dialogue.state = DIALOGUE_STATE_INACTIVE;
}

lobby_state_t
*lobby_get_state(void)
{
    return &g_lobby;
}

/**
 * @brief Load the lobby assets and handle the lobby state
 * @param game Pointer to the game structure
 * @return void
 */
static void
load_assets(void)
{
    SPRITES_8x8;

    set_bkg_data(0, 1, grass_tile);
    set_bkg_data(1, 1, void_tile);
    set_bkg_data(2, 4, tronc_tile);
    set_bkg_data(6, 4, wall_tile);
    set_bkg_data(10, 4, wall_tile_limit);
    set_bkg_data(14, 1, wall_crossing_tile);
    set_bkg_data(15, 4, bush_tile);
    set_bkg_data(19, 4, flower_tile);
    set_bkg_data(23, 4, ennemies1_tile);
    set_bkg_data(27, 4, ennemies2_tile);
    set_bkg_tiles(0, 0, 20, 18, map_bl);

    text_renderer_init();
    dialogue_init();

    set_sprite_data(0, 4, player_tiles_front);
    set_sprite_data(4, 2, player_tile_front_move);
    set_sprite_data(6, 4, player_tile_back);
    set_sprite_data(10, 2, player_tile_back_move);
    set_sprite_data(12, 4, player_tile_left);
    set_sprite_data(16, 2, player_tile_left_move);
    set_sprite_data(18, 4, player_tile_right);
    set_sprite_data(22, 2, player_tile_right_move);

    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);


    move_sprite(0, g_lobby.player_x, g_lobby.player_y);
    move_sprite(1, g_lobby.player_x + 8, g_lobby.player_y);
    move_sprite(2, g_lobby.player_x, g_lobby.player_y + 8);
    move_sprite(3, g_lobby.player_x + 8, g_lobby.player_y + 8);
}

/**
 * @brief Load the current map tiles and the player sprite based on the current movement direction
 */
static void
load_current_map(void)
{
    set_bkg_tiles(0, 0, 20, 18, g_lobby.current_map);
    set_sprite_tile(0, g_lobby.moving_dir + 0);
    set_sprite_tile(1, g_lobby.moving_dir + 1);
    set_sprite_tile(2, g_lobby.moving_dir + 2);
    set_sprite_tile(3, g_lobby.moving_dir + 3);
}

void
lobby(OUT game_t *game)
{
    if (!g_lobby.inited) {
        lobby_init_state();
        save_load(game);
    } else
        g_lobby.should_dialogue = TRUE;
    load_assets();
    load_current_map();
    if (g_lobby.current_map_id == MAP_ID_TC)
        draw_scoreboard(game);
}

/**
 * @brief Move the player sprite based on the current movement state
 * @param game Pointer to the game structure
 * @return void
 */
static void
move_sprite_personage(OUT lobby_state_t *lobby)
{
    UINT8 sens = lobby->moving_dir;

    if (lobby->is_moving) {
        set_sprite_tile(0, sens + 0);
        set_sprite_tile(1, sens + 1);
        if (lobby->fps_counter < 15) {
            set_sprite_tile(2, sens + 4);
            set_sprite_tile(3, sens + 3);
        }
        else if (lobby->fps_counter < 30) {
            set_sprite_tile(2, sens + 2);
            set_sprite_tile(3, sens + 5);
        } else
            lobby->fps_counter = 0;
    } else {
        set_sprite_tile(0, sens + 0);
        set_sprite_tile(1, sens + 1);
        set_sprite_tile(2, sens + 2);
        set_sprite_tile(3, sens + 3);
    }
    lobby->is_moving = FALSE;
}

void
update_lobby(OUT game_t *game)
{
    lobby_state_t *lobby = lobby_get_state();

    lobby->fps_counter++;
    if (lobby->fps_counter >= 60) {
        lobby->fps_counter = 0;
        lobby->seconds_counter++;
    }
    lore_update(game);
    if (game->state != GAME_STATE_LOBBY)
        return;
    move_sprite_personage(lobby);
    move_sprite(0, lobby->player_x, lobby->player_y);
    move_sprite(1, lobby->player_x + 8, lobby->player_y);
    move_sprite(2, lobby->player_x, lobby->player_y + 8);
    move_sprite(3, lobby->player_x + 8, lobby->player_y + 8);
}

