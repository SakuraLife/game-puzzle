
CC=g++
WARNINGS = -Wall -Warray-bounds -Wcast-align -Wfloat-equal -Wfloat-conversion -Winit-self -Winline -Wlogical-op -Wunused -Wmain -Wold-style-cast -Wreturn-type -Wshadow -Wtype-limits
FPIC=-fpic
Os=-O3
std=-std=c++17
LINK = -Wl,-L./
SEARCH = -I./
OBJECTS = io.o map_operation.o check.o utility.o puzzle.o defdata.o
TARGETLIBS = libio.so libmap_operation.so libcheck.so libutility.so  libpuzzle.so libdefdata.so
all: libpuzzle.so libdefdata.so chclean
	mkdir -p ../lib
	mv $(TARGETLIBS) ../lib
	rm -rf ./lib

libio.so : io.o
	$(CC) -shared -o libio.so io.o
io.o: io.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c io.cpp

libmap_operation.so: map_operation.o
	$(CC) -shared -o libmap_operation.so map_operation.o
map_operation.o: map_operation.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c map_operation.cpp

libcheck.so: check.o
	$(CC) -shared -o libcheck.so check.o
check.o: check.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c check.cpp

libutility.so: utility.o libcheck.so libio.so
	mkdir -p ./lib
	cp ./libio.so ./libcheck.so ./lib/
	$(CC) -shared $(LINK) -o libutility.so utility.o ./lib/libio.so ./lib/libcheck.so
utility.o: utility.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c utility.cpp

libpuzzle.so: puzzle.o libutility.so libcheck.so libmap_operation.so
	mkdir -p ./lib
	cp ./libutility.so ./libmap_operation.so ./libcheck.so ./lib/
	$(CC) -shared $(LINK) -o libpuzzle.so puzzle.o ./lib/libutility.so ./lib/libcheck.so ./lib/libmap_operation.so -lpthread
puzzle.o: puzzle.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c puzzle.cpp

libdefdata.so: defdata.o libcheck.so libmap_operation.so
	mkdir -p ./lib
	cp ./libutility.so ./libmap_operation.so ./lib/
	$(CC) -shared $(LINK) -o libdefdata.so defdata.o ./lib/libcheck.so ./lib/libmap_operation.so

defdata.o: defdata.cpp
	$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c defdata.cpp

.PHONY: chclean clean
clean:
	-rm $(OBJECTS)
	-rm $(TARGETLIBS)
chclean:
	-rm $(OBJECTS)
