
CC=g++
WARNINGS = -Wall -Warray-bounds -Wcast-align -Wfloat-equal -Wfloat-conversion -Winit-self -Winline -Wlogical-op -Wunused -Wmain -Wold-style-cast -Wreturn-type -Wshadow -Wtype-limits -Wsign-conversion
FPIC=-fpic
Os=-O3
std=-std=c++17
LINK = -Wl,-rpath,'$$ORIGIN/libpuzzle/:$$ORIGIN/libpuzzle/maps:libpuzzle/:libpuzzle/maps'
LIBSEARCH = -L./buildin -L./build
# LINK = -Wl,-l,.
SEARCH = -Wl,-rpath,'$$ORIGIN'
OBJECT := puzzle.help.o puzzle.main.o
TARGET := puzzle.help puzzle.main
DEPENDS := puzzle.help.d puzzle.main.d
DEFDATADEPEND := $(foreach tmp,$(wildcard ./buildin/*.cpp),$(addprefix -l, $(subst ./buildin/,, $(subst .cpp,,$(tmp)))))

unexport

all: build_in_map libs puzzle.main puzzle.help

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

puzzle.help: puzzle.help.o libs
	$(CC) $(LIBSEARCH) $(LINK) -o puzzle.help puzzle.help.o -lpuzzle

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	echo -e "\t$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) -c $<" >> $@; \
	rm -f $@.$$$$

include $(DEPENDS)

.PHONY: chclean clean install all build_in_map libs

install:
	mkdir -p install
	mkdir -p install/libpuzzle
	mkdir -p install/libpuzzle/maps
	cp $(TARGET) ./install
	cp ./build/*.so ./install/libpuzzle
	cp ./buildin/*.so ./install/libpuzzle/maps

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
