
CC=g++
WARNINGS = -Wall -Warray-bounds -Wcast-align -Wfloat-equal -Wfloat-conversion -Winit-self -Winline -Wlogical-op -Wunused -Wmain -Wold-style-cast -Wreturn-type -Wshadow -Wtype-limits
FPIC=-fpic
Os=-O3
std=-std=c++17
LINK = -Wl,-L./
SEARCH = -I./
OBJECTS = keyboard.o map_operation.o check.o utility.o puzzle.o defdata.o
TARGETLIBS = libkeyboard.so libmap_operation.so libcheck.so libutility.so  libpuzzle.so libdefdata.so

all: libpuzzle.so libdefdata.so
	@mkdir -p ../lib
	cp $(TARGETLIBS) ../lib
	@rm -rf ./lib

libkeyboard.so : keyboard.o
	$(CC) -shared -o libkeyboard.so keyboard.o
keyboard.o: keyboard.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c keyboard.cpp

libmap_operation.so: map_operation.o
	$(CC) -shared -o libmap_operation.so map_operation.o
map_operation.o: map_operation.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c map_operation.cpp

libcheck.so: check.o
	$(CC) -shared -o libcheck.so check.o
check.o: check.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c check.cpp

libutility.so: utility.o libcheck.so libkeyboard.so
	@mkdir -p ./lib
	@cp ./libkeyboard.so ./libcheck.so ./lib/
	$(CC) -shared $(LINK) -o libutility.so utility.o ./lib/libkeyboard.so ./lib/libcheck.so
utility.o: utility.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c utility.cpp

libpuzzle.so: puzzle.o libutility.so libcheck.so libmap_operation.so
	@mkdir -p ./lib
	@cp ./libutility.so ./libmap_operation.so ./libcheck.so ./lib/
	$(CC) -shared $(LINK) -o libpuzzle.so puzzle.o ./lib/libutility.so ./lib/libcheck.so ./lib/libmap_operation.so -lpthread
puzzle.o: puzzle.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c puzzle.cpp

libdefdata.so: defdata.o libcheck.so libmap_operation.so
	@mkdir -p ./lib
	@cp ./libutility.so ./libmap_operation.so ./lib/
	$(CC) -shared $(LINK) -o libdefdata.so defdata.o ./lib/libcheck.so ./lib/libmap_operation.so

defdata.o: defdata.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c defdata.cpp

.PHONY: chclean clean all
clean: chclean
	-rm $(TARGETLIBS)
chclean:
	-rm $(OBJECTS)
