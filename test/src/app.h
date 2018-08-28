#pragma once

#include "coop_tcp_acceptor.h"

typedef struct
{
    scd_scheduler scheduler_;
    coop_tcp_acceptor acceptor_;
    coop_tcp_socket client_;
    char receive_buffer_[2000];
    size_t receive_size_;
} app;

void app_construct(app* inst);
void app_run(app* inst);