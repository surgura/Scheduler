#pragma once
#include <stdint.h>
#include "tcp_socket.h"
#include "scheduler/scheduler.h"
#include "async_executor.h"

typedef struct
{
    scd_scheduler* scheduler_;
    tcp_socket socket_;
    async_executor executor_;

    void(*receive_callback_)(void* user_data);
    void* receive_user_data_;
    size_t* receive_size_;
    char* receive_buffer_;
    size_t receive_buffer_size_;
} coop_tcp_socket;

void coop_tcp_socket_construct(coop_tcp_socket* socket, scd_scheduler* scheduler);
void coop_tcp_socket_destruct(coop_tcp_socket* socket);
void coop_tcp_socket_receive(coop_tcp_socket* socket, void(*callback)(void* user_data), void* user_data, char* buffer, size_t buffer_size, size_t* receive_size);