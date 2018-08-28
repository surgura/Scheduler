#pragma once

#include "coop_tcp_socket.h"
#include "tcp_acceptor.h"
#include "async_executor.h"
#include "scheduler/scheduler.h"

typedef struct
{
    scd_scheduler* scheduler_;
    tcp_acceptor acceptor_;
    async_executor executor_;

    void(*accept_callback_)(void* user_data);
    void* accept_user_data_;
    coop_tcp_socket* accept_socket_;
} coop_tcp_acceptor;

void coop_tcp_acceptor_construct(coop_tcp_acceptor* acceptor, scd_scheduler* scheduler);
void coop_tcp_acceptor_destruct(coop_tcp_acceptor* acceptor);
void coop_tcp_acceptor_accept(coop_tcp_acceptor* acceptor, void(*callback)(void* user_data), void* user_data, coop_tcp_socket* new_socket);