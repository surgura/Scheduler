#include "async_executor.h"
#include <stdio.h>

void async_executor_construct(async_executor* executor)
{
    lfds711_freelist_init_valid_on_current_logical_core(&executor->thread_pool_, NULL, 0, NULL);
    for (int i = 0; i < 16; ++i)
    {
        LFDS711_FREELIST_SET_VALUE_IN_ELEMENT(executor->thread_buffer_[i].fe, &executor->thread_buffer_[i]);
        lfds711_freelist_push(&executor->thread_pool_, &executor->thread_buffer_[i].fe, NULL);
    }
}

void async_executor_destruct(async_executor* executor)
{
    lfds711_freelist_cleanup(&executor->thread_pool_, NULL);
}

DWORD WINAPI async_executor_execute_do(void* data) {
    async_executor_thread_* thread_data = (async_executor_thread_*)data;
    thread_data->task(thread_data->user_data);
    thread_data->interrupt(thread_data->user_data);
    lfds711_freelist_push(&thread_data->executor->thread_pool_, &thread_data->fe, NULL);
    return 0;
}

void async_executor_execute(async_executor* executor, void(*task)(void* user_data), void(*interrupt)(void* user_data), void* user_data)
{
    struct lfds711_freelist_element* fe;
    if (!lfds711_freelist_pop(&executor->thread_pool_, &fe, NULL))
    {
        printf("Error <scd_scd_add>: No elements left in pool.");
        return;
    }
    async_executor_thread_* thread_data = LFDS711_FREELIST_GET_VALUE_FROM_ELEMENT(*fe);
    thread_data->executor = executor;
    thread_data->user_data = user_data;
    thread_data->interrupt = interrupt;
    thread_data->task = task;
    CreateThread(NULL, 0, async_executor_execute_do, thread_data, 0, NULL);
}