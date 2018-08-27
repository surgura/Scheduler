#include "scheduler/scheduler.h"
#include <stdio.h>
#include "tcp_acceptor.h"

scd_scheduler scheduler;
scd_conditional cond1;
scd_conditional cond2;

void processor_sleep(void* user_data)
{

}

void processor_awake(void* user_data)
{
    
}

/*
void interrupt1()
{

}

void send_udp_messages(void* user_data);

void on_send_done(void* user_data)
{
    // TODO read data
    send_udp_messages(0);
}

void send_udp_messages(void* user_data)
{
    scd_cnd_construct(&cond1);
    // TODO set iterrupt routine
    scd_scd_add_conditional(&scheduler, &cond1, on_send_done, 0);
    // TODO enable
}




void read_uart_messages(void* user_data);

void on_read_done(void* user_data)
{
    // TODO read data
    read_uart_messages(0);
}

void read_uart_messages(void* user_data)
{
    scd_cnd_construct(&cond2);
    // TODO set iterrupt routine
    scd_scd_add_conditional(&scheduler, &cond1, on_read_done, 0);
    // TODO enable
}*/

tcp_socket client;

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
}

void accept_connection(void* user_data)
{
    printf("Creating acceptor\n");
    tcp_acceptor acceptor;
    tcp_acceptor_construct(&acceptor);
    
    printf("Waiting for connection\n");
    tcp_acceptor_accept_one(&acceptor, &client);

    printf("Closing acceptor\n");
    tcp_acceptor_destruct(&acceptor);

    scd_scd_add(&scheduler, receive_messages, 0);
}

int main()
{
    scd_scd_construct(&scheduler, processor_sleep, processor_awake, 0);
    scd_scd_add(&scheduler, accept_connection, 0);
    scd_scd_run(&scheduler);

    return 0;
}