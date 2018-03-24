
CC=g++
WARNINGS = -Wall -Warray-bounds -Wcast-align -Wfloat-equal -Wfloat-conversion -Winit-self -Winline -Wlogical-op -Wunused -Wmain -Wold-style-cast -Wreturn-type -Wshadow -Wtype-limits -Wsign-conversion
FPIC=-fpic
Os=-O3
std=-std=c++14
LINK = -Wl,-rpath,'$$ORIGIN/libpuzzle/:$$ORIGIN/libpuzzle/maps:libpuzzle/:libpuzzle/maps'
LIBSEARCH = -L./buildin -L./build
# LINK = -Wl,-l,.
SEARCH = -Wl,-rpath,'$$ORIGIN'
OBJECT := puzzle.gen.o puzzle.main.o
TARGET := puzzle.gen puzzle.main
DEPENDS := puzzle.gen.d puzzle.main.d
NDEBUG =
ifndef DESTDIR
	DESTDIR := ./install
endif
ifdef DEBUG
	NDEBUG := 0
else
	NDEBUG := 1
endif

export NDEBUG

all: build_in_map libs puzzle.main puzzle.gen

build_in_map:
	@$(MAKE) -C ./buildin
	@mkdir -p ./libpuzzle/maps
	@ln -rsf -t ./libpuzzle/maps ./buildin/*.so

libs: build_in_map
	@$(MAKE) -C ./build
	@mkdir -p ./libpuzzle
	@ln -rsf -t ./libpuzzle ./build/*.so

puzzle.main: puzzle.main.o libs build_in_map
	$(CC) $(LIBSEARCH) $(LINK) -o puzzle.main puzzle.main.o -lpuzzle -ldefdata

puzzle.gen: puzzle.gen.o libs
	$(CC) $(LIBSEARCH) $(LINK) -o puzzle.gen puzzle.gen.o -lpuzzle

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	echo -e "\t$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) -c $<" >> $@; \
	rm -f $@.$$$$

include $(DEPENDS)

.PHONY: chclean clean install all build_in_map libs

install:
	mkdir -p "${DESTDIR}"
	mkdir -p "${DESTDIR}/libpuzzle"
	cp $(TARGET) "${DESTDIR}"
	cp ./build/*.so "${DESTDIR}/libpuzzle"
	cp ./buildin/*.so "${DESTDIR}/libpuzzle"

chclean:
	@$(MAKE) -C ./build chclean
	@$(MAKE) -C ./buildin chclean
	-rm $(OBJECT)
	-rm $(DEPENDS)
	-rm -rf ./libpuzzle

clean: chclean
	@$(MAKE) -C ./build clean
	@$(MAKE) -C ./buildin clean
	-rm $(TARGET)
