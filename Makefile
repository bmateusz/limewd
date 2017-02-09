
ifdef REL
CFLAGS=-c -flto -O3 -Wall -Wextra -std=c99
ADDLDFLAGS=-flto
else ifdef TRAVIS
CFLAGS=-c -g -Wall -Wextra -std=c99
else
CFLAGS=-c -g -Wall -Wextra -std=c99
ADDLDFLAGS=-fsanitize=address,leak,undefined
endif

LDFLAGS=-lmicrohttpd -lsqlite3 -lduktape -lm $(ADDLDFLAGS)
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
