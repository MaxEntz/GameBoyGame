##
## EPITECH PROJECT, 2026
## gameboy
## File description:
## Makefile
##

TARGET  =   game

GBDK_HOME ?= /opt/gbdk
LCC     ?=   $(GBDK_HOME)/bin/lcc

SRC     =   $(shell find src/ -name "*.c")
ASSET   =   $(shell find asset/src/ -name "*.c")

# yt 1b = MBC5 + RAM + BATTERY
# yo x = x rom banks (16KB)
# ya x = x ram banks (8KB)
CFLAGS  =   -Wa-l -Wl-m -Wl-j -Iinclude/ -Iasset/include/ \
            -Wm-yt1b -Wm-yo8 -Wm-ya1

all: $(TARGET).gb

$(TARGET).gb: $(SRC) $(ASSET)
	$(LCC) $(CFLAGS) -o $(TARGET).gb $(SRC) $(ASSET)

clean:
	rm -f *.o *.lst *.map *.sym *.noi *.rel *.ihx

fclean: clean
	rm -f $(TARGET).gb

re: fclean all

.PHONY: all clean fclean re