# GameBoyGame

A small Game Boy homebrew project built with [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020).

## Overview

This repository contains the source code for a Game Boy project structured around a minimal core loop. The current entry point initializes the project core and keeps the game running inside a `vsync()` loop.

## Requirements

Before building the project, make sure you have the following installed on your machine:

- A C toolchain capable of running `lcc` from GBDK-2020
- `make`
- A Game Boy emulator if you want to test the generated ROM locally

## Installing GBDK-2020

### Option 1: Official release

1. Download the latest GBDK-2020 release from the official repository:
   https://github.com/gbdk-2020/gbdk-2020
2. Extract the archive to a directory of your choice.
3. Add the `bin/` directory to your `PATH` so the `lcc` compiler is available from the terminal.

Example:

```sh
export GBDK_HOME="$HOME/gbdk"
export PATH="$GBDK_HOME/bin:$PATH"
```

To make this persistent, add those lines to your shell configuration file such as `~/.zshrc`.

### Option 2: Homebrew

If a formula is available on your system, you can also install GBDK-2020 with Homebrew:

```sh
brew install gbdk-2020
```

If the formula is not available, use the official release instead.

## Building the project

From the root of the repository, run:

```sh
make
```

This command builds the project and generates the `game.gb` ROM file.

## Cleaning build artifacts

Remove intermediate object and build files with:

```sh
make clean
```

Remove every generated file, including the ROM:

```sh
make fclean
```

Rebuild everything from scratch:

```sh
make re
```

## Project Structure

```text
include/
  core.h
  project_types.h
src/
  main/
    core.c
    main.c
Makefile
```
