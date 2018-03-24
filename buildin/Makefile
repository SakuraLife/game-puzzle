CC=g++
WARNINGS = -Wall -Warray-bounds -Wcast-align -Wfloat-equal -Wfloat-conversion -Winit-self -Winline -Wlogical-op -Wunused -Wmain -Wold-style-cast -Wreturn-type -Wshadow -Wtype-limits -Wsign-conversion
FPIC=-fpic
Os=-O3
std=-std=c++14
LINK = -Wl,-L./
LIBSEARCH = -L./ -L../build
SOURCE := $(wildcard *.cpp)
OBJECTS := $(foreach tmp,$(SOURCE),$(subst .cpp,.o,$(tmp)))
DEPENDS := $(foreach tmp,$(SOURCE),$(subst .cpp,.d,$(tmp)))
TARGET := libmap.so
HEADERS := $(wildcard *.h)

all: pre libmap.so
	@cat /dev/null > ./build_in.hpp
	@$(foreach tmp, $(HEADERS), echo "#include\"${tmp}\"" >> ./build_in.hpp;)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	echo -e "\t$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) -c $<" >> $@; \
	rm -f $@.$$$$

pre:
	@$(MAKE) -C ../build libmap_operation.so

libmap.so: $(OBJECTS)
	$(CC) $(LIBSEARCH) -shared -o libmap.so $(OBJECTS) -lmap_operation

include $(DEPENDS)

.PHONY: all clean chclean pre

chclean:
	-rm $(OBJECTS)
	-rm $(DEPENDS)

clean: chclean
	-rm $(TARGET)
