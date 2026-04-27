/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** lobby.c
*/

#include "lobby/lobby.h"
#include <stdio.h>

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
    set_bkg_data(1, 1, wall_tile);
    set_bkg_tiles(0, 0, 20, 18, map);
    set_sprite_data(0, 4, player_tiles);

    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);

    move_sprite(0, 80, 80);
    move_sprite(1, 88, 80);
    move_sprite(2, 80, 88);
    move_sprite(3, 88, 88);

}

static void
calculate_velocity(OUT game_t *game)
{
    if (!game->is_jumping && game->velocity_y < MAX_FALL_SPEED)
        game->velocity_y += GRAVITY;
}

static void
applicate_gravity(OUT game_t *game)
{
    calculate_velocity(game);
    if (game->is_jumping) {
        if (game->player_y > game->jump_limit + JUMP_SPEED)
            game->player_y -= JUMP_SPEED;
        else {
            game->player_y = game->jump_limit;
            game->is_jumping = FALSE;
            game->velocity_y = 0;
        }
    } else if (game->player_y < SCREEN_HEIGHT - SPRITE_SIZE) {
        if (game->player_y + game->velocity_y > SCREEN_HEIGHT - SPRITE_SIZE)
            game->player_y = SCREEN_HEIGHT - SPRITE_SIZE;
        else
            game->player_y += game->velocity_y;
    }
}

void
lobby(OUT game_t *game)
{
    (void)game;
    load_assets();
}

void
update_lobby(OUT game_t *game)
{
    game->fps_counter++;
    if (game->fps_counter >= 60) {
        game->fps_counter = 0;
        game->seconde_counter++;
    }

    applicate_gravity(game);
    move_sprite(0, game->player_x, game->player_y);
    move_sprite(1, game->player_x + 8, game->player_y);
    move_sprite(2, game->player_x, game->player_y + 8);
    move_sprite(3, game->player_x + 8, game->player_y + 8);
}

void
handle_input_lobby(OUT game_t *game,
                   IN UINT8 keys)
{
    if (keys & J_A)
        game_changer(game, GAME_STATE_MG2);
    if (keys & J_LEFT && game->player_x > 16)
        game->player_x -= SPEED;
    if (keys & J_RIGHT && game->player_x < SCREEN_WIDTH - SPRITE_SIZE)
        game->player_x += SPEED;
    if (keys & J_UP && game->player_y > 8 + SPRITE_SIZE && game->is_jumping == FALSE) {
        game->is_jumping = TRUE;
        game->jump_limit = game->player_y - JUMP_FORCE;
        game->velocity_y = 0;
    }
    if (keys & J_DOWN && game->player_y < SCREEN_HEIGHT - SPRITE_SIZE)
        game->player_y += SPEED;
}
