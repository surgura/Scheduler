#include "async_executor.h"

void async_executor_construct(async_executor* executor)
{

}

void async_executor_destruct(async_executor* executor)
{

}

void async_executor_execute(async_executor* executor, void(*task)(void* user_data), void(*interrupt)(), void* user_data)
{
    // TODO
    task(user_data);
    interrupt();
}