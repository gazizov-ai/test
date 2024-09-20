#include <stdio.h>
#include "lclnt_funcs1.h"

void do_regular_work()
{
    printf("super sleep 1.0\n");
    sleep(10);
}

int main(int ac, char ** av)
{
    setup();
    if (get_ticket() != 0) exit(0);
    do_regular_work();
    release_ticket();
    shut_down();
}
