LFDS711_LOCATION = /home/aart/Libraries/liblfds711
CC = gcc
LIB_NAME = libScheduler.a

CFLAGS = -Wall -Wextra -O3
INCLUDE = -Iinclude/scheduler -I$(LFDS711_LOCATION)/inc
OBJ_DIR = ./obj
LIB_DIR = ./lib

SOURCES = scheduler.c
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

make: $(LIB_NAME)

$(LIB_NAME): $(OBJECTS)
	ar rcs lib/$(LIB_NAME) obj/$(OBJECTS)

%.o: src/%.c dirmake
	$(CC) -c $(INCLUDE) $(CFLAGS) -o obj/$@ $<
	
dirmake:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIB_DIR)
	
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) Makefile.bak

rebuild: clean build