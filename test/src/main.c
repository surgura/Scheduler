#include "scheduler/scheduler.h"
#include <unistd.h>

scd_conditional cond1;

void interrupt1()
{

}

void fiber1()
{
    sleep(100); // work
    scd_cnd_construct(&cond1);
    // set iterrupt routine
    // enable
}

int main()
{
    scd_scheduler scheduler;

    return 0;
}