##
## EPITECH PROJECT, 2025
## gameboy
## File description:
## Makefile
##

TARGET  =   game

GBDK_HOME ?= /opt/gbdk
LCC     ?=   $(GBDK_HOME)/bin/lcc

SRC     =   $(shell find src/ -name "*.c")

CFLAGS  =   -Wa-l -Wl-m -Wl-j -Iinclude/

all: $(TARGET).gb

$(TARGET).gb: $(SRC)
	$(LCC) $(CFLAGS) -o $(TARGET).gb $(SRC)

clean:
	rm -f *.o *.lst *.map *.sym *.noi *.rel *.ihx

fclean: clean
	rm -f $(TARGET).gb

re: fclean all

.PHONY: all clean fclean re