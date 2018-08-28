#include "scheduler.h"
#include <stdbool.h>
#include <stdio.h>

void scd_scd_construct(scd_scheduler* scheduler, void* user_data)
{
    lfds711_freelist_init_valid_on_current_logical_core(&scheduler->task_pool_, NULL, 0, NULL);
    for (int i = 0; i < 16; ++i)
    {
        LFDS711_FREELIST_SET_VALUE_IN_ELEMENT(scheduler->task_pool_buffer_[i].fe, &scheduler->task_pool_buffer_[i]);
        lfds711_freelist_push(&scheduler->task_pool_, &scheduler->task_pool_buffer_[i].fe, NULL);
    }

    lfds711_queue_bmm_init_valid_on_current_logical_core(&scheduler->task_queue_state_, scheduler->task_queue_buffer, sizeof(scheduler->task_queue_buffer)/sizeof(struct lfds711_queue_bmm_element), NULL );
}

void scd_scd_destruct(scd_scheduler* scheduler)
{
    lfds711_queue_bmm_cleanup(&scheduler->task_queue_state_, NULL);
    lfds711_freelist_cleanup(&scheduler->task_pool_, NULL);
}

void scd_scd_run(scd_scheduler* scheduler)
{
    // while stuff in queue
    while (true)
    {
        struct lfds711_freelist_element* fe;
        if (lfds711_queue_bmm_dequeue(&scheduler->task_queue_state_, NULL, (void**)&fe))
        {
            scd_task_fe_* task_wrapper = LFDS711_FREELIST_GET_VALUE_FROM_ELEMENT(*fe);
            task_wrapper->task.task(task_wrapper->task.user_data);
            lfds711_freelist_push(&scheduler->task_pool_, fe, NULL);
        }
        // TODO maybe sleep while nothing in queue
    }
}

void scd_scd_add(scd_scheduler* scheduler, void(*task)(void* user_data), void* user_data)
{
    struct lfds711_freelist_element* fe;
    if (!lfds711_freelist_pop(&scheduler->task_pool_, &fe, NULL))
    {
        printf("Error <scd_scd_add>: No elements left in pool.");
        return;
    }
    scd_task_fe_* task_wrapper = LFDS711_FREELIST_GET_VALUE_FROM_ELEMENT(*fe);
    task_wrapper->task.task = task;
    task_wrapper->task.user_data = user_data;
    lfds711_queue_bmm_enqueue(&scheduler->task_queue_state_, NULL, fe);
}

void scd_scd_add_conditional(scd_scheduler* scheduler, scd_conditional* cond, void(*task)(void* user_data), void* user_data)
{

}