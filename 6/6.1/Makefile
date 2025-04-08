
TARGET = phonebook

LIBRARY = libsource.a
LIST_SRC = source.c
LIST_OBJ = source.o

MAIN_SRC = main.c
MAIN_OBJ = main.o

CC = gcc
CFLAGS = -Wall -g
AR = ar
ARFLAGS = rcs

.PHONY: all clean

all: $(TARGET)

$(LIBRARY): $(LIST_OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(MAIN_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) -L. -lsource

clean:
	rm -f $(TARGET) $(LIBRARY) $(LIST_OBJ) $(MAIN_OBJ)

