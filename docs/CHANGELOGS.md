# Changelog

All notable changes to this project will be documented in this file.

This format is based on Keep a Changelog  
and this project adheres to Semantic Versioning. (MAJOR.MINOR.PATCH)

---

## [1.16.0] - 2026-05-14

### Added
- **Collision logic in `src/mg3/flappy.c`**: Implemented `check_collision()` to detect impacts between the bird and pipes.

---

## [1.15.0] - 2026-05-14

### Added
- Trap Memory game enhancements:
  - Game finished state and victory condition handling
  - Round tracking with adjustable round logic
  - Block movement flag to control player movement during game state transitions
  - Enhanced safe tile visibility logic with progression through levels
  - Game over detection and player position recalculation

### Changed
- `include/mg1/trap_memory.h`: Updated `TIME_SEE_SAFE_TILE` definition for improved level progression
- `src/mg1/trap_memory.c`: Enhanced game structure and added round timing logic with map clearing functionality

### Fixed
- Player position calculation in game over checks
- Safe tile visibility adjustments for proper level difficulty progression

---

## [1.14.0] - 2026-05-12

### Added
- `src/lobby/lore_lobby.c` / `include/lobby/lore_lobby.h`: new files for all lore logic (dialogue texts, NPC interaction, post-dialogue transitions)
- Full 9 dialogues (left bro (0-2), right bro (3-5), center room boss (6-8)), each with a lose loop and a win branch
- `should_dialogue` bool in `lobby_state_tused on return from games
- Center room (`MAP_ID_CC`) auto-triggers dialogue 6 when the player enters
- Player repositioned to `y=72` before center room dialogue to avoid sprite overlapping the dialogue box
- Scoreboard added on TC map, showing best and current scores for all mini-games

### Changed
- `src/lobby/input_handler_lobby.c`: separated functions in smaller helpers
---

## [1.13.0] - 2026-06-12

### Added
- Flappy Bird logic: Implementation of the core gameplay loop for the `MG3` mini-game.
- `asset/include/mg3/asset_flappy.h` & `src/mg3/asset_flappy.c`: New assets for the FlappyBird game.
- `include/mg3/mg3_layout.h`: New layout definitions for the game interface.
- `src/mg3/flappy.c`: Main game logic and pipe management.

## Fixed
- Overflow prevention: Changed the data type of `bird_y` to prevent calculation overflows.
- Boundary Clamping: Added a limit to the bird's position to prevent it from leaving the screen area.
- Visual fixes: Corrected an issue where pipes were displayed incorrectly at the start of the game.
- Merge conflicts: Resolved conflicts in the latest integration.

### Changed
- `src/main/core.c`: Integrated the new game mode into the core engine.
- Refactoring & Macros: Replaced hard-coded values with macros for better maintainability and renamed variables for clarity.
- Randomization: Improved the pipe generation logic using a more robust `rand()` implementation.


## [1.11.2] - 2026-05-08

### Changed
- `src/lobby*`: update all lobby file to delete the uneused function for the lobby

---

## [1.12.0] - 2026-05-09

### Added
- Start menu state with full 160×144 background (takes 256 tiles frmom the vram)
- `asset/src/menu/asset_menu.c`: 256 2bpp tiles + 20×18 tilemap
- `src/common/vram_clear.c`: `vram_clear()` utility to zero all 256 VRAM bg tile slots
- `game_changer` now takes a boolean third argument; clears VRAM after fade-out when `TRUE`

### Changed
- `include/common/game_changer.h` / `src/common/game_changer.c`: added `clear_vram` parameter
- All `game_changer` call sites updated for the new parameter:
- `src/menu/menu.c`: removed `vram_clear()` call from load function
- `src/lobby/lobby.c`: removed `vram_clear()` call from `load_assets`

---

## [1.11.1] - 2026-05-06

### Changed
- `src/mg2/tetris_piece.c`: `piece_can_move_left` and `piece_can_move_right` now call to `piece_fits`
- `src/mg2/tetris.c`: added `handle_piece_lock` and `handle_left_right` static to improve readability of `update_tetris` and `handle_input_tetris`
- `src/mg2/tetris.c`: `tetris()` init now calls `spawn_next()` instead of manually setting piece fields; first piece is now random
- `src/mg2/tetris_hud.c`: `draw_next_piece` merged clear and draw into a single loop

---

## [1.11.0] - 2026-05-04

### Added
- Line clearing: full rows detected, erased, playfield redrawn when lines are cleared
- Scoring system, dependig on cleared line count
- Lines counter and level progression
- Gravity speed scaling with level
- Game over detection, returning to lobby on game over
- Next piece preview displayed in the NEXT box
- COmmon random functions, with an inittializer and a getter
- Use of the rng for the piece spawning in tetris

### Changed
- `include/common/common.h`: added `level` field to `game_t`
- `include/mg2/tetris_layout.h`: `DROP_DELAY` replaced by `DROP_DELAY_BASE`, `DROP_DELAY_STEP`, `DROP_DELAY_MIN`, `LINES_PER_LEVEL`
- `src/mg2/tetris.c`: moved HUD calls to `tetris_hud.c`
- `src/lobby/input_handler_lobby.c`: seeds RNG on first key press

---

## [1.10.0] - 2026-05-03

### Added
- Lobby transition at the start of the game
- Complete map management system with modular map changer logic
- Multiple maps support for the lobby with easy map selection logic
- Portal-based map transition system
- Enemy selection management with A input control
- Input handler module for improved lobby input separation
- New lobby assets:
  - Bush assets for environment decoration
  - Flower assets for visual enhancement
  - New enemy character for MG launcher
  - Updated cl1 character sprite
  - Portal tile for map transitions
  - Map border and limit assets
- Improved game checker logic for game selection

### Fixed
- Lobby input handler code cleanup to avoid code duplication
- Left move cursor positioning (y=16 alignment)
- Map manager code cleanup to eliminate duplication
- Removed unused includes

### Changed
- `src/lobby/` : Modularized into separate files for input handling, map management, and transitions
- `asset/src/asset_lobby.c` : Expanded with new lobby assets
- `include/common/common.h` : Extended with new common types
- `include/lobby/lobby.h` : Added new struct definitions and function prototypes

---

## [1.9.1] - 2026-05-02

### Added
- Adding the total score, score mg1... in the core struct

### Changed
- `include/common/common.h`: added the var into the struct

---

## [1.9.0] - 2026-05-01

### Added
- Adding all basic sprite for the mole game
- Adding the collision with the map number
- Update the sprite and animate it

### Changed
- `asset/` : added all asset for the lobby
- `src/lobby/lobby.c` : Update code to ensure the motion for all sprite

---

## [1.8.0] - 2026-04-29

### Added
- Piece downward movement acceleration
- Piece rotation with collision detection (clockwise and counterclockwise)
- `can_rotate` flag to prevent multiple rotations from a single button press

### Changed
- `include/mg2/tetris_piece.h` : added `can_rotate` boolean to `piece_t` struct, and new function prototypes for `rotate_r` and `rotate_l`
- `src/mg2/tetris_piece.c` : `piece_shapes` array updated to include all 4 rotation states for each piece

---

## [1.7.0] - 2026-04-28

### Added
- Left/right movement for pieces with wall and grid collision detection
- `move_frame` counter to throttle horizontal input (avoids instant clipping), configurable via `MOVE_DELAY` in `tetris_layout.h`

### Fixed
- `include/mg2/tetris_piece.h` : changed `x` from `UINT8` to `INT8` in `piece_t` struct to allow negative values for the pieces (used for the O tile)
---

## [1.6.0] - 2026-04-28

### Added
- Grid for the tetris playfield (10*18)
- Pieces as a double array of 4x4, with 7 pieces
- Piece struct with type, rotation, and position variables (not all implemented yet)
- Piece drawing and erasing functions
- Piece locking and collision detection functions
- Pseudo-random piece spawning (cycling through the 7 pieces in order for now)
- Basic graity for the pieces (only moving down, no player input yet)

### Changed
- `include` : Renamed `mg2*.h` to `tetris*.h` for clarity

---

## [1.5.0] - 2026-04-27

### Added
- Add mg3.h with function prototypes for Flappy Bird (init, update, input).
- Create flappy.c with empty function stubs to ensure initial compilation.
- Set up the foundational architecture for MG3 development.

### Changed
-`src/mg3/flappy.c`: The base of the base of flappy bird only proto
-`include/mg3/flappy.h`: The base of the base too. Only proto.

---

## [1.4.0] - 2026-04-27

### Added
- layout constants for playfield, HUD, and NEXT box positions
- 20×18 tilemap for MG2 background
- 9 new 2bpp tiles: decorative NEXT box frame (4 corners, top/bottom edges, left/right edges) + full black tile
- HUD labels (SCORE, LEVEL, LINES)
- NEXT piece preview box

### Changed
- `src/mg2/tetris.c`: full visual load replacing the placeholder
- `include/mg2/mg2.h`: cleaned up includes, removed `asset_lobby` dependency
- `asset_tetris.h/c`: removed redundant individual tile arrays, only `tetris_tiles[]` and `tetris_bg_map[]` exposed
- `TETRIS_TILE_COUNT` updated to 18

### Fixed
- Lobby player sprite remaining visible on MG2 screen

---

## [1.3.0] - 2026-04-24

### Added
- Asset pipeline for MG2 Tetris: `asset/include/mg2/asset_tetris.h` and `asset/src/mg2/asset_tetris.c`
- 10 placeholder 2bpp tiles: empty cell, border, 7 block pieces, HUD frame
- `tetris_tile_id_e` enum and `TETRIS_TILE_COUNT` / `TETRIS_TILE_SIZE` constants for symbol names
- MG2 asset guide in `docs/TECH.md`: VRAM loading, tile table, and sprite replacement workflow

### Changed
- Nothing yet

### Fixed
- No bug fixes yet

---

## [1.3.0] - 2026-04-24

### Added
- Asset pipeline for MG2 Tetris: `asset/include/mg2/asset_tetris.h` and `asset/src/mg2/asset_tetris.c`
- 10 placeholder 2bpp tiles: empty cell, border, 7 block pieces, HUD frame
- `tetris_tile_id_e` enum and `TETRIS_TILE_COUNT` / `TETRIS_TILE_SIZE` constants for symbol names
- MG2 asset guide in `docs/TECH.md`: VRAM loading, tile table, and sprite replacement workflow

### Changed
- Nothing yet

### Fixed
- No bug fixes yet

---

## [1.2.0] - 2026-04-23

### Added
- Base sprite tiles for characters
- Dialogue system: letter-by-letter text with sound effect
- Dialogue box rendered from a tilemap asset
- 2 lines per page, up to 18 characters per line for dialogues
- A/B input handling during dialogue: skip animation, advance page, or close the box
- Typing sound effect on each non-space character
- Font asset extended with punctuation: `.` `,` `!` `?` `'` `-`

### Changed
- Core game loop to support dialogue state and rendering
- Tetris input handling to trigger a sample dialogue

### Fixed
- No bug fixes yet

---

## [1.1.0] - 2026-04-20

### Added
- Added a transition effect between screens
- Added sound effects for transitions, with 4 stages
- Added a tetris 'game' (copy of the lobby) to test the transition effect

### Changed
- Lobby input handling to use the new transition effect

### Fixed
- No bug fixes yet

---

## [1.0.0] - 2026-04-17

### Added
- Project initialization
- Basic folder structure setup
- First screen display
- Handle the key management and update
- All the project base is modular

### Changed
- Nothing yet

### Fixed
- No bug fixes yet

---
