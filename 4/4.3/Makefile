CC=gcc
SOURCES=main.c source.c
FLAGS=-Werror -Wall -Wextra
OUTPUT=phonebook

.PHONY: default all build clean

default: all

all: build

build:
	$(CC) $(FLAGS) $(SOURCES) -o $(OUTPUT)

clean:
	rm -rf $(OUTPUT)