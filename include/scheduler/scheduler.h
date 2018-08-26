#pragma once

#include "conditional.h"

typedef struct
{
    
} scd_scheduler;

void scd_scd_add_conditional(scd_conditional* cond, void(*task)(void* user_data));