/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** trap_memory.h
*/

#ifndef TRAP_MEMORY_H_
    #define TRAP_MEMORY_H_

    #include "common/common.h"
    #include "common/game_changer.h"
    #include "common/text_renderer.h"
    #include "common/random.h"
    #include "asset_lobby.h"

typedef struct trap_memory_s {
    UINT8      player_x;
    UINT8      player_y;
} trap_memory_t;

/**
 * @brief Load the Trap Memory assets and handle its state
 * @param game Pointer to the game structure
 * @return void
 */
void
trap_memory(OUT game_t *game);

/**
 * @brief Update Trap Memory
 * @param game Pointer to the game structure
 * @return void
 */
void
update_trap_memory(OUT game_t *game);

/**
 * @brief Handle the input for Trap Memory
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_trap_memory(OUT game_t *game,
                        IN UINT8 keys);

#endif /* !TRAP_MEMORY_H_ */
