
CC=g++
WARNINGS = -Wall -Warray-bounds -Wcast-align -Wfloat-equal -Wfloat-conversion -Winit-self -Winline -Wlogical-op -Wunused -Wmain -Wold-style-cast -Wreturn-type -Wshadow -Wtype-limits
FPIC=-fpic
Os=-O3
std=-std=c++17
LINK = -Wl,-L./
SEARCH = -I./
SOURCE := $(wildcard *.cpp)
OBJECTS := $(foreach tmp,$(SOURCE),$(subst .cpp,.o,$(tmp)))
DEPENDS := $(foreach tmp,$(SOURCE),$(subst .cpp,.d,$(tmp)))
TARGETLIBS := $(foreach tmp,$(SOURCE),$(addprefix lib, $(subst .cpp,.so,$(tmp))))
DEFDATADEPEND := $(foreach tmp,$(wildcard ../build_in/*.cpp),$(addprefix ./buildin/lib, $(subst ../build_in/,, $(subst .cpp,.so,$(tmp)))))

all: $(TARGETLIBS)

libkeyboard.so libcheck.so libmap_operation.so libutility.so: lib%.so: %.o
	$(CC) -shared -o $@ $<

libpuzzle.so: puzzle.o libutility.so libcheck.so libmap_operation.so libsolve.so libmain.so
	@mkdir -p ./lib
	@ln -rsf -t ./lib ./libmap_operation.so ./libcheck.so ./libmain.so ./libutility.so ./libsolve.so
	$(CC) -shared $(LINK) -o libpuzzle.so puzzle.o ./lib/libutility.so ./lib/libcheck.so ./lib/libmap_operation.so ./lib/libsolve.so ./lib/libmain.so -lpthread

libdefdata.so: defdata.o
	@mkdir -p ./buildin
	@ln -rsf -t ./buildin ../build_in/*.so
	$(CC) -shared $(LINK) -o libdefdata.so defdata.o $(DEFDATADEPEND)

libmain.so libsolve.so: lib%.so: %.o libutility.so libkeyboard.so libcheck.so
	@mkdir -p ./lib
	@ln -rsf -t ./lib ./libkeyboard.so ./libcheck.so ./libutility.so
	$(CC) -shared $(LINK) -o $@ $< ./lib/libkeyboard.so ./lib/libcheck.so ./lib/libutility.so

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	echo -e "\t$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c $<" >> $@; \
	rm -f $@.$$$$

include $(DEPENDS)

.PHONY: chclean clean all

chclean:
	-rm -r ./lib
	-rm -r ./buildin
	-rm $(OBJECTS)

clean: chclean
	-rm $(TARGETLIBS)
	-rm $(DEPENDS)
