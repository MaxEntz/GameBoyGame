/*
** EPITECH PROJECT, 2026
** GameBoyGame
** File description:
** menu.h
*/

#ifndef MENU_H_
    #define MENU_H_

    #include "common/common.h"
    #include "common/game_changer.h"
    #include "common/text_renderer.h"
    #include "menu/asset_menu.h"

/**
 * @brief Load the start menu assets
 * 
 * @param game Pointer to the game structure
 * @return void
 */
void
menu(OUT game_t *game);

/**
 * @brief Handle input in the start menu state
 * 
 * @param game Pointer to the game structure
 * @param keys The keys pressed
 * @return void
 */
void
handle_input_menu(OUT game_t *game,
                  IN UINT8 keys);

/**
 * @brief Update the start menu state
 * 
 * @param game Pointer to the game structure
 * @return void
 */
void
update_menu(OUT game_t *game);

#endif /* !MENU_H_ */
