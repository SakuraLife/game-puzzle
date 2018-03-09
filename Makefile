
CC=g++
WARNINGS = -Wall -Warray-bounds -Wcast-align -Wfloat-equal -Wfloat-conversion -Winit-self -Winline -Wlogical-op -Wunused -Wmain -Wold-style-cast -Wreturn-type -Wshadow -Wtype-limits
FPIC=-fpic
Os=-O3
std=-std=c++17
LINK = -Wl,-L./
SEARCH = -I./
OBJECT = puzzle.help.o puzzle.main.o
TARGET = puzzle.help puzzle.main

unexport

all: libs puzzle.main puzzle.help

libs:
	@$(MAKE) -C ./build

puzzle.main: puzzle.main.o ./lib/libio.so ./lib/libutility.so ./lib/libmap_operation.so ./lib/libcheck.so ./lib/libpuzzle.so ./lib/libdefdata.so
	$(CC) -o puzzle.main puzzle.main.o ./lib/libio.so ./lib/libutility.so ./lib/libmap_operation.so ./lib/libcheck.so ./lib/libdefdata.so ./lib/libpuzzle.so

puzzle.main.o: puzzle.main.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c puzzle.main.cpp

puzzle.help: puzzle.help.o ./lib/libio.so ./lib/libutility.so ./lib/libmap_operation.so ./lib/libcheck.so ./lib/libpuzzle.so
	$(CC) -o puzzle.help puzzle.help.o ./lib/libio.so ./lib/libutility.so ./lib/libmap_operation.so ./lib/libcheck.so ./lib/libpuzzle.so

puzzle.help.o: puzzle.help.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c puzzle.help.cpp

.PHONY: clean install all

install:
	mkdir -p ./install
	cp $(TARGET) ./install
	cp -r ./lib ./install

chclean:
	-rm $(OBJECT)

clean: chclean
	-rm -r ./lib
	-rm $(TARGET)
