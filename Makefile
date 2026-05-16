##
## EPITECH PROJECT, 2026
## gameboy
## File description:
## Makefile
##

TARGET  =   game

GBDK_HOME ?= /opt/gbdk
LCC     ?=   $(GBDK_HOME)/bin/lcc
DOXYGEN ?=   doxygen

SRC     =   $(shell find src/ -name "*.c")
ASSET   =   $(shell find asset/src/ -name "*.c")

# yt 27 = MBC5 + RAM + BATTERY (0x1B)
# yo x = x rom banks (16KB)
# ya x = x ram banks (8KB)
CFLAGS  =   -Wa-l -Wl-m -Wl-j -Iinclude/ -Iasset/include/ \
            -Wm-yt27 -Wm-yo8 -Wm-ya1

all: $(TARGET).gb

$(TARGET).gb: $(SRC) $(ASSET)
	$(LCC) $(CFLAGS) -o $(TARGET).gb $(SRC) $(ASSET)

clean:
	rm -f *.o *.lst *.map *.sym *.noi *.rel *.ihx

fclean: clean
	rm -f $(TARGET).gb

re: fclean all

doc:
	$(DOXYGEN) docs/Doxyfile

.PHONY: all clean fclean re doc