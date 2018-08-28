CC := gcc

all:
	${CC} src/main.c src/tcp_acceptor.c src/tcp_socket.c src/async_executor.c src/coop_tcp_socket.c src/coop_tcp_acceptor.c src/app.c -o test -I../include -L../lib -lscheduler -IC:/liblfds7.1.1/inc -LC:\liblfds7.1.1\bin -llfds711 -lws2_32

clean:
	rm test