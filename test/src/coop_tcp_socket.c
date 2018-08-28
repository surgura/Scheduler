#include "coop_tcp_socket.h"

void coop_tcp_socket_construct(coop_tcp_socket* socket, scd_scheduler* scheduler)
{
    socket->scheduler_ = scheduler;
    async_executor_construct(&socket->executor_);
}

void coop_tcp_socket_destruct(coop_tcp_socket* socket)
{
    async_executor_destruct(&socket->executor_);
    tcp_socket_destruct(&socket->socket_);
}

void receive_do(void* user_data)
{
    coop_tcp_socket* socket = (coop_tcp_socket*)user_data;
    *socket->receive_size_ = tcp_socket_receive(&socket->socket_, socket->receive_buffer_, socket->receive_buffer_size_);
}

void receive_done(void* user_data)
{
    coop_tcp_socket* socket = (coop_tcp_socket*)user_data;
    scd_scd_add(socket->scheduler_, socket->receive_callback_, socket->receive_user_data_);
}

void coop_tcp_socket_receive(coop_tcp_socket* socket, void(*callback)(void* user_data), void* user_data, char* buffer, size_t buffer_size, size_t* receive_size)
{
    socket->receive_callback_ = callback;
    socket->receive_user_data_ = user_data;
    socket->receive_buffer_ = buffer;
    socket->receive_buffer_size_ = buffer_size;
    socket->receive_size_ = receive_size;

    async_executor_execute(&socket->executor_, receive_do, receive_done, socket);
}