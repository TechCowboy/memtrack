#include <stdio.h>
#include <stdlib.h>

#define MEMTRACK_ON
#include "memtrack.h"

void main(void)
{
    void *a,*b,*c;

    a = MT_Malloc(1024);
    for(int i=0; i<10; i++)
    {
        b = MT_Malloc(512);
    }

    for (int i = 0; i < 20; i++)
    {
        c = MT_Calloc(100, 20);
    }
    MT_Free(a);
    MT_Free(b);
    MT_Free(c);

    MT_Free(a);

    mem_list();

    mem_list_by_file_and_line();

}