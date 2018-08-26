#pragma once

typedef struct
{

} scd_conditional;

// set callback and arm
void scd_cnd_construct(scd_conditional* cond);
void scd_cnd_arm(scd_conditional* cond, void(*on_fullfill)(void* user_data));
void scd_cnd_fullfill(scd_conditional* cond);