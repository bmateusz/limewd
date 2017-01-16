
ifdef REL
CC=gcc-6 -flto
CFLAGS=-c -O3 -Wall
else ifdef CLANG
CC=clang
CFLAGS=-c -O0 -Wall
else
CC=gcc-6
CFLAGS=-c -g -Wall
ADDLDFLAGS=-fsanitize=address,leak,undefined
endif

LDFLAGS=-lm -lmicrohttpd -lsqlite3 $(ADDLDFLAGS)
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:src/%.c=src/.%.o) lib/duktape/src/.duktape.o
DEPENDENCIES=$(OBJECTS:.o=.d)
EXECUTABLE=myway

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
