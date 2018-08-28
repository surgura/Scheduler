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

/*
void receive_messages(void* user_data)
{
    char buffer[2000];
    int recv_size = tcp_socket_receive(&client, buffer, sizeof(buffer)/sizeof(char)-1);
    if (recv_size != 0)
    {
        buffer[recv_size] = '\0';
        printf("%s\n", buffer);
    }
    else
    {
        tcp_socket_destruct(&client);
        return;
    }
    receive_messages(0);
}*/

void accept_connection_done(void* user_data)
{
    printf("Client accepted.\n");
}

void accept_connection(void* user_data)
{
    printf("Accepting client..\n");
    coop_tcp_acceptor_accept(&acceptor, accept_connection_done, NULL, &client);
}

void fake_work(void* user_data)
{
    printf("Starting fake work\n");
    sleep(1);
    printf("Fake work done\n");
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