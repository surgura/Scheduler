#include "scheduler/scheduler.h"
#include <stdio.h>

scd_scheduler scheduler;
scd_conditional cond1;
scd_conditional cond2;

void sleep(void* user_data)
{

}

void awake(void* user_data)
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

void send_udp_messages(void* user_data)
{
    printf("send_udp_messages\n");
}

void read_uart_messages(void* user_data)
{
    printf("read_uart_messages\n");
}


int main()
{
    scd_scd_construct(&scheduler, sleep, awake, 0);
    scd_scd_add(&scheduler, send_udp_messages, 0);
    scd_scd_add(&scheduler, read_uart_messages, 0);
    scd_scd_run(&scheduler);

    return 0;
}