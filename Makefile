
CC=clang
LDFLAGS=-lmicrohttpd -lsqlite3
CFLAGS=-c -O0 -Wall
SOURCES=$(wildcard *.c) $(wildcard src/*.c)
OBJECTS=$(SOURCES:src/%.c=src/.%.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
EXECUTABLE=myway

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

-include $(DEPENDENCIES)

.%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM -MF $(@:.o=.d) -MT $@ $(CFLAGS) $<

.PHONY: clean
clean:
	rm -fv $(OBJECTS) $(DEPENDENCIES) $(EXECUTABLE)

