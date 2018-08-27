#pragma once

#include "conditional.h"
#include "liblfds711.h"

typedef struct
{
    void(*task)(void* user_data);
    void* user_data;
} scd_task_;

typedef struct
{
    struct lfds711_freelist_element fe;
    scd_task_ task;
} scd_task_fe_;

typedef struct
{
    struct lfds711_queue_bmm_element task_queue_buffer[16];

    struct lfds711_queue_bmm_state task_queue_state_;

    scd_task_fe_ task_pool_buffer_[16];

    struct lfds711_freelist_state task_pool_;
} scd_scheduler;

void scd_scd_construct(scd_scheduler* scheduler, void(*sleep)(void* user_data), void(*awake)(void* user_data), void* user_data);
void scd_scd_run(scd_scheduler* scheduler);
void scd_scd_add(scd_scheduler* scheduler, void(*task)(void* user_data), void* user_data);
void scd_scd_add_conditional(scd_scheduler* scheduler, scd_conditional* cond, void(*task)(void* user_data), void* user_data);