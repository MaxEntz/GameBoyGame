/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** save_select.h
*/

#ifndef SAVE_SELECT_H_
    #define SAVE_SELECT_H_

    #include "common/common.h"
    #include "common/game_changer.h"
    #include "common/save.h"
    #include "common/text_renderer.h"
    #include "asset_lobby.h"
    #include "menu/asset_save_select.h"
    #include <string.h>

/**
 * @brief Load the start save_select assets
 * 
 * @param game Pointer to the game structure
 * @return void
 */
void
save_select(OUT game_t *game);

/**
 * @brief Handle input in the start save_select state
 * 
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_save_select(OUT game_t *game,
                  IN UINT8 keys);

/**
 * @brief Update the start save_select state
 * 
 * @param game Pointer to the game structure
 * @return void
 */
void
update_save_select(OUT game_t *game);

/**
 * @brief Choose the difficulty level
 * 
 * @param game Pointer to the game structure
 * @return void
 */
void
choose_difficulty(OUT game_t *game);

/**
 * @brief Handle input in the choose difficulty state
 * 
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_choose_difficulty(OUT game_t *game,
                               IN UINT8 keys);

/**
 * @brief Update the choose difficulty state
 * 
 * @param game Pointer to the game structure
 * @return void
 */
void
update_choose_difficulty(OUT game_t *game);



#endif /* !SAVE_SELECT_H_ */