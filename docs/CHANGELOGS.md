# Changelog

All notable changes to this project will be documented in this file.

This format is based on Keep a Changelog  
and this project adheres to Semantic Versioning. (MAJOR.MINOR.PATCH)

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
