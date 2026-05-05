# Changelog

All notable changes to this project will be documented in this file.

This format is based on Keep a Changelog  
and this project adheres to Semantic Versioning. (MAJOR.MINOR.PATCH)
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
