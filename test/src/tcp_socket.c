#include "tcp_socket.h"

void tcp_socket_construct(tcp_socket* sock)
{
    // TODO
}

void tcp_socket_destruct(tcp_socket* sock)
{
    closesocket(sock->sock);
}

int tcp_socket_receive(tcp_socket* sock, char* buffer, size_t buffer_size)
{
    int recv_size;

    if((recv_size = recv(sock->sock , buffer , buffer_size , 0)) == 0)
    {
        printf("recv failed\n");
        printf("%i\n", WSAGetLastError());
        return 0;
    }
    return recv_size;
}