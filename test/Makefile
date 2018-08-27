CC := gcc

all:
	${CC} src/main.c src/tcp_acceptor.c src/tcp_socket.c -o test -I../include -L../lib -lscheduler -IC:/liblfds7.1.1/inc -LC:\liblfds7.1.1\bin -llfds711 -lws2_32

clean:
	rm test