
ifdef REL
CC=gcc -flto
CFLAGS=-c -O3 -Wall -std=c11
else ifdef CLANG
CC=clang
CFLAGS=-c -O0 -Wall -std=c11
else
CC=gcc
CFLAGS=-c -g -Wall -std=c11
ADDLDFLAGS=-fsanitize=address,leak,undefined
endif

LDFLAGS=-lm -lmicrohttpd -lsqlite3 -lduktape $(ADDLDFLAGS)
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:src/%.c=src/.%.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
EXECUTABLE=lmwd

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

-include $(DEPENDENCIES)

.%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	@$(CC) -MM -MF $(@:.o=.d) -MT $@ $(CFLAGS) $<

.PHONY: clean tag doc
clean:
	$(RM) $(OBJECTS) $(DEPENDENCIES) $(EXECUTABLE)

tag:
	$(RM) tags
	ctags -R -h ".c.h"

doc:
	doxygen
