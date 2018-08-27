#pragma once

#include <stdio.h>
#include <winsock2.h>
#include <stdbool.h>

typedef struct
{
    SOCKET sock;
} tcp_socket;

void tcp_socket_construct(tcp_socket* sock);
void tcp_socket_destruct(tcp_socket* sock);
int tcp_socket_receive(tcp_socket* sock, char* buffer, size_t buffer_size);