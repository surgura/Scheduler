#include "app.h"
#include <unistd.h>

void receive_message(void* user_data);
void receive_message_done(void* user_data)
{
    app* inst = (app*)user_data;
    printf("Message received.\n");

    if (inst->receive_size_ != 0)
    {
        inst->receive_buffer_[inst->receive_size_] = '\0';
        printf("%s\n", inst->receive_buffer_);
    }
    else
    {
        printf("Receive failed.\n");
        coop_tcp_socket_destruct(&inst->client_);
        return;
    }

    receive_message(inst);
}

void receive_message(void* user_data)
{
    app* inst = (app*)user_data;
    printf("Receiving message..\n");
    coop_tcp_socket_receive(&inst->client_, receive_message_done, inst, inst->receive_buffer_, sizeof(inst->receive_buffer_)/sizeof(char)-1, &inst->receive_size_);
}

void accept_connection_done(void* user_data)
{
    app* inst = (app*)user_data;
    printf("Client accepted.\n");
    receive_message(inst);
}

void accept_connection(void* user_data)
{
    app* inst = (app*)user_data;
    printf("Accepting client..\n");
    coop_tcp_socket_construct(&inst->client_, &inst->scheduler_);
    coop_tcp_acceptor_accept(&inst->acceptor_, accept_connection_done, inst, &inst->client_);
}

void fake_work(void* user_data)
{
    app* inst = (app*)user_data;
    sleep(1);
    printf("BUSY\n");
    scd_scd_add(&inst->scheduler_, fake_work, inst);
}

void app_construct(app* inst)
{
    scd_scd_construct(&inst->scheduler_, 0);
}

void app_run(app* inst)
{
    coop_tcp_acceptor_construct(&inst->acceptor_, &inst->scheduler_);

    scd_scd_add(&inst->scheduler_, accept_connection, inst);
    scd_scd_add(&inst->scheduler_, fake_work, inst);
    scd_scd_run(&inst->scheduler_);

}