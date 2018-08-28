#pragma once
#include <stdint.h>
#include "tcp_socket.h"

typedef struct
{
    tcp_socket socket_;
} coop_tcp_socket;

void coop_tcp_socket_construct(coop_tcp_socket* socket);
void coop_tcp_socket_destruct(coop_tcp_socket* socket);
void coop_tcp_socket_receive(coop_tcp_socket* socket, void(*callback)(void* user_data), void* user_data, char* buffer, size_t buffer_size);