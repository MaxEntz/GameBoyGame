/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** flappy.h
*/

#ifndef FLAPPY_H_
    #define FLAPPY_H_

    #include "common/common.h"
    #include "common/game_changer.h"
    #include "mg3/mg3_layout.h"
    #include "mg3/asset_flappy.h"
    #include "common/random.h"
    #include "common/asset_common_font.h"
    #include "common/text_renderer.h"

    typedef struct pipe_s {
        INT16 pipe_x;
        INT16 pipe_y;
    } pipe_t;


    typedef struct flappy_s {
        INT16 bird_y;
        UINT8 pipes_passed;
        UINT8 pipe_speed;
        UINT8 jump_force;
        UINT8 pipe_gap;
        pipe_t pipes[MG3_NB_PIPE];
    } flappy_t;

/**
 * @brief Load the Flappy Bird assets and handle its state
 * @param game Pointer to the game structure
 * @return void
 */
void
flappybird(OUT game_t *game);

/**
 * @brief Update of Flappy Bird
 * @param game Pointer to the game structure
 * @return void
 */
void
update_flappybird(OUT game_t *game);

/**
 * @brief Handle the input handle of Flappy Bird
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_flappybird(OUT game_t *game, 
                        IN UINT8 keys);

#endif /* FLAPPY_H_ */
