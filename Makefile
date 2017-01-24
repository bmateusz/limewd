
ifdef REL
CC=gcc-6 -flto
CFLAGS=-c -O3 -Wall -Wpedantic
else ifdef CLANG
CC=clang
CFLAGS=-c -O0 -Wall -Wpedantic
else
CC=gcc-6
CFLAGS=-c -g -Wall -Wpedantic
ADDLDFLAGS=-fsanitize=address,leak,undefined
endif

LDFLAGS=-lm -lmicrohttpd -lsqlite3 $(ADDLDFLAGS)
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:src/%.c=src/.%.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
ADDOBJECTS=lib/duktape/src/.duktape.o
EXECUTABLE=lmwd

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(ADDOBJECTS)
	$(CC) $(OBJECTS) $(ADDOBJECTS) $(LDFLAGS) -o $@

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
