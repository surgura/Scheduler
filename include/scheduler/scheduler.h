#pragma once

#include "conditional.h"

typedef struct
{
    
} scd_scheduler;

void scd_scd_construct(scd_scheduler* scheduler);
void scd_scd_run(scd_scheduler* scheduler);
void scd_scd_add(scd_scheduler* scheduler, void(*task)(void* user_data), void* user_data);
void scd_scd_add_conditional(scd_scheduler* scheduler, scd_conditional* cond, void(*task)(void* user_data), void* user_data);