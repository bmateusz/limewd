
ifdef REL
CFLAGS=-c -flto -O3 -Wall -Wextra -std=c99
ADDLDFLAGS=-flto
else ifdef TRAVIS
CFLAGS=-c -g -Wall -Wextra -std=c99
else
CFLAGS=-c -g -Wall -Wextra -std=c99
ADDLDFLAGS=-fsanitize=address,leak,undefined
endif

LDFLAGS=-lmicrohttpd -lsqlite3 -lm $(ADDLDFLAGS)
SOURCES=$(wildcard src/*.c) external/duktape/src/duktape.c
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
DEPENDENCIES=$(OBJECTS:.o=.d)
EXECUTABLE=lmwd

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

-include $(DEPENDENCIES)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	@$(CC) -MM -MF $(@:.o=.d) -MT $@ $(CFLAGS) $<

.PHONY: clean tags doc tidy
clean:
	$(RM) $(OBJECTS) $(DEPENDENCIES) $(EXECUTABLE)

tags:
	$(RM) tags
	ctags -R -h ".c.h"

doc:
	doxygen

tidy:
	clang-tidy $(SOURCES)
