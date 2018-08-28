#include "coop_tcp_acceptor.h"

void coop_tcp_acceptor_construct(coop_tcp_acceptor* acceptor, scd_scheduler* scheduler)
{
    acceptor->scheduler_ = scheduler;
    async_executor_construct(&acceptor->executor_);
    tcp_acceptor_construct(&acceptor->acceptor_);
}

void coop_tcp_acceptor_destruct(coop_tcp_acceptor* acceptor)
{
    tcp_acceptor_destruct(&acceptor->acceptor_);
    async_executor_destruct(&acceptor->executor_);
}

void accept_do(void* user_data)
{
    coop_tcp_acceptor* acceptor = (coop_tcp_acceptor*)user_data;
    tcp_acceptor_accept_one(&acceptor->acceptor_, &acceptor->accept_socket_->socket_);
}

void accept_done(void* user_data)
{
    coop_tcp_acceptor* acceptor = (coop_tcp_acceptor*)user_data;
    scd_scd_add(acceptor->scheduler_, acceptor->accept_callback_, acceptor->accept_user_data_);
}

void coop_tcp_acceptor_accept(coop_tcp_acceptor* acceptor, void(*callback)(void* user_data), void* user_data, coop_tcp_socket* new_socket)
{
    acceptor->accept_callback_ = callback;
    acceptor->accept_user_data_ = user_data;
    acceptor->accept_socket_ = new_socket;
    async_executor_execute(&acceptor->executor_, accept_do, accept_done, acceptor);
}