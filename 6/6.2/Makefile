TARGET = phonebook
LIBRARY = libsource.so
LIST_SRC = source.c
LIST_OBJ = source.o
MAIN_SRC = main.c
MAIN_OBJ = main.o
CC = gcc
CFLAGS = -Wall -g -fPIC
LDFLAGS = -L. -Wl,-rpath=.
LDLIBS = -lsource

all: $(TARGET)

.PHONY: all clean

$(LIBRARY): $(LIST_OBJ)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.

$(TARGET): $(MAIN_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(TARGET) $(LIBRARY) $(LIST_OBJ) $(MAIN_OBJ)
