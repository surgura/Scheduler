#include "scheduler/scheduler.h"
#include <stdio.h>
#include "coop_tcp_acceptor.h"
#include "async_executor.h"
#include <unistd.h>

scd_scheduler scheduler;
scd_conditional cond1;
scd_conditional cond2;

void processor_sleep(void* user_data)
{

}

void processor_awake(void* user_data)
{
    
}

coop_tcp_acceptor acceptor;
coop_tcp_socket client;
char receive_buffer[2000];
size_t receive_size;

void receive_message(void* user_data);
void receive_message_done(void* user_data)
{
    printf("Message received.\n");

    if (receive_size != 0)
    {
        receive_buffer[receive_size] = '\0';
        printf("%s\n", receive_buffer);
    }
    else
    {
        printf("Receive failed.\n");
        coop_tcp_socket_destruct(&client);
        return;
    }

    receive_message(NULL);
}

void receive_message(void* user_data)
{
    printf("Receiving message..\n");
    coop_tcp_socket_receive(&client, receive_message_done, NULL, receive_buffer, sizeof(receive_buffer)/sizeof(char)-1, &receive_size);
}

void accept_connection_done(void* user_data)
{
    printf("Client accepted.\n");
    receive_message(NULL);
}

void accept_connection(void* user_data)
{
    printf("Accepting client..\n");
    coop_tcp_socket_construct(&client, &scheduler);
    coop_tcp_acceptor_accept(&acceptor, accept_connection_done, NULL, &client);
}

void fake_work(void* user_data)
{
    sleep(1);
    printf("BUSY\n");
    scd_scd_add(&scheduler, fake_work, 0);
}

int main()
{
    scd_scd_construct(&scheduler, processor_sleep, processor_awake, 0);
    coop_tcp_acceptor_construct(&acceptor, &scheduler);

    scd_scd_add(&scheduler, accept_connection, 0);
    scd_scd_add(&scheduler, fake_work, 0);
    scd_scd_run(&scheduler);

    return 0;
}