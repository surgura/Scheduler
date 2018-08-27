#pragma once

#include "tcp_socket.h"

typedef struct
{
    WSADATA wsa;
    SOCKET accept_socket;
    struct sockaddr_in server_addr;
} tcp_acceptor;

void tcp_acceptor_construct(tcp_acceptor* acceptor);
void tcp_acceptor_destruct(tcp_acceptor* acceptor);
void tcp_acceptor_accept_one(tcp_acceptor* acceptor, tcp_socket* new_socket);