CC = g++
CXFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wformat-security -Werror
CXDEBUG = -g
CXVER = -std=c++20
SRC = src/*.cpp
INCLUDE = include/

compile:
	$(CC) $(CXFLAGS) $(CXVER) -I$(INCLUDE) $(SRC) -o tp2

debug:
	$(CC) $(CXFLAGS) $(CXVER) $(CXDEBUG) -I$(INCLUDE) $(SRC) -o tp2

all:
	compile
