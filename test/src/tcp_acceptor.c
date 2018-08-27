#include "tcp_acceptor.h"

void tcp_acceptor_construct(tcp_acceptor* acceptor)
{
    if (WSAStartup(MAKEWORD(2,2), &acceptor->wsa) != 0)
    {
        printf("Failed. Error Code : %d\n",WSAGetLastError());
    }

    if((acceptor->accept_socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d\n" , WSAGetLastError());
    }
 
    //Prepare the sockaddr_in structure
    acceptor->server_addr.sin_family = AF_INET;
    acceptor->server_addr.sin_addr.s_addr = INADDR_ANY;
    acceptor->server_addr.sin_port = htons( 8888 );
     
    //Bind
    if( bind(acceptor->accept_socket ,(struct sockaddr *)&acceptor->server_addr , sizeof(acceptor->server_addr)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d\n" , WSAGetLastError());
    }

    listen(acceptor->accept_socket , 3);
}

void tcp_acceptor_destruct(tcp_acceptor* acceptor)
{
    closesocket(acceptor->accept_socket);
}

void tcp_acceptor_accept_one(tcp_acceptor* acceptor, tcp_socket* new_socket)
{
    struct sockaddr_in client;
    int client_size = sizeof(struct sockaddr_in);
    new_socket->sock = accept(acceptor->accept_socket, (struct sockaddr *)&client, &client_size);
    if (new_socket->sock == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d\n" , WSAGetLastError());
    }
}