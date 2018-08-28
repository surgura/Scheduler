#pragma once

#include <windows.h>
#include "liblfds711.h"

struct async_executor;
typedef struct
{
    void(*task)(void* user_data);
    void(*interrupt)(void* user_data);
    void* user_data;
    struct lfds711_freelist_element fe;
    struct async_executor* executor;
} async_executor_thread_;

typedef struct async_executor
{
    async_executor_thread_ thread_buffer_[16];
    struct lfds711_freelist_state thread_pool_;
} async_executor;

void async_executor_construct(async_executor* executor);
void async_executor_destruct(async_executor* executor);
void async_executor_execute(async_executor* executor, void(*task)(void* user_data), void(*interrupt)(void* user_data), void* user_data);