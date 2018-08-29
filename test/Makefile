LFDS711_LOCATION = /home/aart/Libraries/liblfds711
CC = gcc
BIN_NAME = test

CFLAGS = -Wall -Wextra -O3
INCLUDE = -I../include -I$(LFDS711_LOCATION)/inc
OBJ_DIR = ./obj
BIN_DIR = ./bin
LINKDIRS = -L../lib -L$(LFDS711_LOCATION)/bin
LINK = -lscheduler -llfds711 -lws2_32

SOURCES = main.c tcp_acceptor.c tcp_socket.c async_executor.c coop_tcp_socket.c coop_tcp_acceptor.c app.c
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

make: $(BIN_NAME)

$(BIN_NAME): $(OBJECTS)
	$(CC) -o $(BIN_DIR)/$(BIN_NAME) $(LINKDIRS) $(LINK) obj/$(OBJECTS)

%.o: src/%.c dirmake
	$(CC) -c $(INCLUDE) $(CFLAGS) -o obj/$@ $<
	
dirmake:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	
clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) Makefile.bak

rebuild: clean build