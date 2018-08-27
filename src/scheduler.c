#include "scheduler.h"
#include <stdbool.h>

void scd_scd_construct(scd_scheduler* scheduler, void(*sleep)(void* user_data), void(*awake)(void* user_data), void* user_data)
{
    lfds711_queue_bmm_init_valid_on_current_logical_core(&scheduler->task_queue_state_, scheduler->task_queue_buffer, sizeof(scheduler->task_queue_buffer)/sizeof(struct lfds711_queue_bmm_element), NULL );
    //TODO lfds711_freelist_init_valid_on_current_logical_core( &fs, ea, 4, NULL );
    for (int i = 0; i < 16; ++i)
    {
        LFDS711_FREELIST_SET_VALUE_IN_ELEMENT(scheduler->task_pool_buffer_[i].fe, &scheduler->task_pool_buffer_[i]);
        lfds711_freelist_push(&scheduler->task_pool_, &scheduler->task_pool_buffer_[i].fe, NULL); // TODO NULL
    }
}

void scd_scd_destruct(scd_scheduler* scheduler)
{
    lfds711_queue_bmm_cleanup( &scheduler->task_queue_state_, NULL );
}

void scd_scd_run(scd_scheduler* scheduler)
{
    // while stuff in queue
    while (true)
    {
        scd_task_* task;
        if (lfds711_queue_bmm_dequeue(&scheduler->task_queue_state_, NULL, (void**)&task))
        {
            task->task(task->user_data);
            // TODO remove task from memory
        }
        // TODO maybe sleep while nothing in queue
    }
}

void scd_scd_add(scd_scheduler* scheduler, void(*task)(void* user_data), void* user_data)
{
    //lfds711_queue_bmm_enqueue( &qbmms, NULL, &td );
}

void scd_scd_add_conditional(scd_scheduler* scheduler, scd_conditional* cond, void(*task)(void* user_data), void* user_data)
{

}