/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lobby.c
*/

#include "lobby/lobby.h"

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
    set_bkg_tiles(0, 0, 20, 18, map_bl);
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


    move_sprite(0, 80, 80);
    move_sprite(1, 88, 80);
    move_sprite(2, 80, 88);
    move_sprite(3, 88, 88);

}

void
lobby(OUT game_t *game)
{
    (void)game;
    load_assets();
    transition_fade_in();
}

/**
 * @brief Move the player sprite based on the current movement state
 * @param game Pointer to the game structure
 * @return void
 */
static void
move_sprite_personage(OUT game_t *game)
{
    UINT8 sens = game->moving_dir;

    if (game->is_moving) {
        set_sprite_tile(0, sens + 0);
        set_sprite_tile(1, sens + 1);
        if (game->fps_counter < 15) {
            set_sprite_tile(2, sens + 4);
            set_sprite_tile(3, sens + 3);
        }
        else if (game->fps_counter < 30) {
            set_sprite_tile(2, sens + 2);
            set_sprite_tile(3, sens + 5);
        } else
            game->fps_counter = 0;
    } else {
        set_sprite_tile(0, sens + 0);
        set_sprite_tile(1, sens + 1);
        set_sprite_tile(2, sens + 2);
        set_sprite_tile(3, sens + 3);
    }
    game->is_moving = FALSE;
}

void
update_lobby(OUT game_t *game)
{
    game->fps_counter++;
    if (game->fps_counter >= 60) {
        game->fps_counter = 0;
        game->seconds_counter++;
    }

    move_sprite_personage(game);
    move_sprite(0, game->player_x, game->player_y);
    move_sprite(1, game->player_x + 8, game->player_y);
    move_sprite(2, game->player_x, game->player_y + 8);
    move_sprite(3, game->player_x + 8, game->player_y + 8);
}

