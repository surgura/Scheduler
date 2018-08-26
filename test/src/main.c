#include "scheduler/scheduler.h"

scd_scheduler scheduler;
scd_conditional cond1;

void interrupt1()
{

}

void read_udp_messages(void* user_data);

void on_send_done(void* user_data)
{
    // TODO read data
    read_udp_messages(0);
}

void read_udp_messages(void* user_data)
{
    scd_cnd_construct(&cond1);
    // TODO set iterrupt routine
    // TODO enable
    scd_scd_add_conditional(&scheduler, &cond1, on_send_done, 0);
}

int main()
{
    scd_scd_construct(&scheduler);
    scd_scd_add(&scheduler, read_udp_messages, 0);
    scd_scd_run(&scheduler);

    return 0;
}