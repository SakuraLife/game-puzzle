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
TARGET := $(foreach tmp,$(SOURCE),$(addprefix lib, $(subst .cpp,.so,$(tmp))))
HEADERS := $(wildcard *.h)

all: pre $(TARGET)
	@cat /dev/null > ./build_in.hpp
	@$(foreach tmp, $(HEADERS), echo "#include\"${tmp}\"" >> ./build_in.hpp;)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	echo -e "\t$(CC) $(WARNINGS) $(FPIC) $(Os) $(std) $(LINK) -c $<" >> $@; \
	rm -f $@.$$$$

pre:
	@$(MAKE) libmap_operation.so -C ../build
	@mkdir -p ./lib
	@ln -rsf -t ./lib ../build/libmap_operation.so

$(TARGET): lib%.so: %.o
	$(CC) -shared -o $@ $< ./lib/libmap_operation.so

include $(DEPENDS)

.PHONY: all clean chclean pre

chclean:
	-rm $(OBJECTS)
	-rm $(DEPENDS)
clean: chclean
	-rm $(TARGET)
	-rm -r ./lib
