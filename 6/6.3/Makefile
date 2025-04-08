TARGET = calculator

LIB_SUMM = libsumm.so
LIB_SUBB = libsubb.so
LIB_MULL = libmull.so
LIB_DIVV = libdivv.so

MAIN_SRC = main.c
MAIN_OBJ = main.o
SOURCE_SRC = source.c
SOURCE_OBJ = source.o
SUMM_SRC = summ.c
SUMM_OBJ = summ.o
SUBB_SRC = subb.c
SUBB_OBJ = subb.o
MULL_SRC = mull.c
MULL_OBJ = mull.o
DIVV_SRC = divv.c
DIVV_OBJ = divv.o

LIBS = $(LIB_SUMM) $(LIB_SUBB) $(LIB_MULL) $(LIB_DIVV)

CC = gcc
CFLAGS = -Wall -g -fPIC
LDFLAGS = -L. -Wl,-rpath=. -ldl

.PHONY: all clean

all: $(TARGET) $(LIBS)

$(TARGET): $(MAIN_OBJ) $(SOURCE_OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) $(SOURCE_OBJ) $(LDFLAGS)

lib%.so: %.o
	$(CC) -shared -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.

clean:
	rm -f $(TARGET) $(LIBS) *.o
