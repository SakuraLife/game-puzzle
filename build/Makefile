
CC=g++
WARNINGS = -Wall -Warray-bounds -Wcast-align -Wfloat-equal -Wfloat-conversion -Winit-self -Winline -Wlogical-op -Wunused -Wmain -Wold-style-cast -Wreturn-type -Wshadow -Wtype-limits -Wsign-conversion
FPIC=-fpic
Os=-O3
std=-std=c++14
LIBSEARCH = -L./ -L../buildin
SEARCH = -I./
SOURCE := $(wildcard *.cpp)
OBJECTS := $(foreach tmp,$(SOURCE),$(subst .cpp,.o,$(tmp)))
DEPENDS := $(foreach tmp,$(SOURCE),$(subst .cpp,.d,$(tmp)))
TARGETLIBS := $(foreach tmp,$(SOURCE),$(addprefix lib, $(subst .cpp,.so,$(tmp))))
DEFDATADEPEND := -lmap
DEBUGARG =

ifeq ($(NDEBUG),1)
	DEBUGARG += -DNDEBUG
endif


all: $(TARGETLIBS)

libkeyboard.so libcheck.so libmap_operation.so libutility.so: lib%.so: %.o
	$(CC) -shared -o $@ $<

libpuzzle.so: puzzle.o libutility.so libcheck.so libmap_operation.so libsolve.so libmain.so libanalyze.so
	$(CC) -shared $(LIBSEARCH) -o libpuzzle.so puzzle.o -lutility -lcheck -lmap_operation -lsolve -lanalyze -lmain -lpthread

libbuildin:
	make -C ../buildin

libdefdata.so: defdata.o libbuildin
	$(CC) -shared $(LIBSEARCH) -o libdefdata.so defdata.o $(DEFDATADEPEND)

libanalyze.so: analyze.o libcheck.so
	$(CC) -shared $(LIBSEARCH) -o libanalyze.so analyze.o -lcheck

libmain.so libsolve.so: lib%.so: %.o libutility.so libkeyboard.so libcheck.so
	$(CC) -shared $(LIBSEARCH) -o $@ $< -lkeyboard -lcheck -lutility

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	echo -e "\t$(CC) $(WARNINGS) $(FPIC) $(Os) $(DEBUGARG) $(std) -c $<" >> $@; \
	rm -f $@.$$$$

include $(DEPENDS)

.PHONY: chclean clean all

chclean:
	-rm -r ./libpuzzle
	-rm $(OBJECTS)
	-rm $(DEPENDS)

clean: chclean
	-rm $(TARGETLIBS)
