#include <stdio.h>
#include "app.h"

int main()
{
    app inst;
    app_construct(&inst);
    app_run(&inst);

    return 0;
}