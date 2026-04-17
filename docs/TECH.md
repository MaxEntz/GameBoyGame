# Tech Stack — Projet GBDK

> Documentation technique du projet. À compléter au fur et à mesure.

---

## Stack technique

| Élément | Détail |
|---|---|
| **Langage** | C (ANSI C / C89) |
| **SDK** | [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020) |
| **Compilateur** | SDCC (Small Device C Compiler) |
| **Émulateur** | [BGB](https://bgb.bircd.org/) / [SameBoy](https://sameboy.github.io/) |
| **Éditeur** | VS Code + extension C/C++ |
| **OS de dev** | Windows / Linux / macOS |

---

## Architecture du projet

```
cartridge/
├── src/
│   ├── common/               #Structure et macro
│   ├── lobby/
│   ├── main/                 #Le core du projet
│   ├── mg1/                  #MiniGame 1
│   └── ...
├── asset/
│   ├── include/      
│   └── src/
├── docs/
│   └── CHANGELOGS.md         #Change Logs
├── Makefile
└── game.gb
```

---

## Setup & Installation

### 1. Installer GBDK-2020

Télécharger la dernière release sur [github.com/gbdk-2020/gbdk-2020](https://github.com/gbdk-2020/gbdk-2020/releases) et extraire l'archive.

```bash
# Exemple sous Linux
export GBDK=/chemin/vers/gbdk
export PATH=$GBDK/bin:$PATH
```

### 2. Compiler le projet

```bash
make
```

### 3. Lancer dans l'émulateur

```bash
bgb build/game.gb
# ou
sameboy build/game.gb
```

---

## Makefile de base

```makefile
GBDK    = /chemin/vers/gbdk
CC      = $(GBDK)/bin/lcc
CFLAGS  = -Wa-l -Wl-m -Wl-j

SRC     = $(wildcard src/*.c)
OUT     = build/game.gb

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f build/*.gb build/*.map build/*.noi
```

---

## Exemple minimal — Hello World

```c
#include <gb/gb.h>
#include <stdio.h>

void main(void) {
    // Tous les calls pour instancié

    while(1) {
        wait_vbl_done(); // Attendre le VBlank
    }
}
```

---

## Conventions de code

- **Nommage** : `snake_case` pour les fonctions et variables
- **Fichiers** : un `.h` par module, inclusions protégées par `#ifndef`
- **Commentaires** : en français (ou anglais, à définir)
- **Sprites** : dans le futur -> convertis via [GBTD/GBMB](http://www.devrs.com/gb/hmgd/gbtd.html) ou [img2gb](https://github.com/flozz/img2gb)

---

## Ressources & références

- [GBDK-2020 Docs](https://gbdk-2020.github.io/gbdk-2020/)
- [Pan Docs — Game Boy Technical Reference](https://gbdev.io/pandocs/)
- [GBDev Discord](https://gbdev.io/chat)
- [Awesome Game Boy Dev](https://github.com/gbdev/awesome-gbdev)

---

> *Dernière mise à jour : 17/04/26*