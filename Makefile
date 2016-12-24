
ifdef REL
CC=gcc-6 -flto
CFLAGS=-c -O3 -Wall
else ifdef CLANG
CC=clang
CFLAGS=-c -O0 -Wall
else
CC=cc
CFLAGS=-c -g -Wall
endif

LDFLAGS=-lmicrohttpd -lsqlite3
SOURCES=$(wildcard *.c) $(wildcard src/*.c)
OBJECTS=$(SOURCES:src/%.c=src/.%.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
EXECUTABLE=myway

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

-include $(DEPENDENCIES)

.%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	@$(CC) -MM -MF $(@:.o=.d) -MT $@ $(CFLAGS) $<

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(DEPENDENCIES) $(EXECUTABLE)

tag: tags
	$(RM) tags
	ctags -R -h ".c.h"
