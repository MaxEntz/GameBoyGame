# Changelog

All notable changes to this project will be documented in this file.

This format is based on Keep a Changelog  
and this project adheres to Semantic Versioning. (MAJOR.MINOR.PATCH)

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
