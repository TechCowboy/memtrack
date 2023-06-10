#define MEMTRACK_ON

#include "memtrack.h"
#include <stdio.h>
#include <malloc.h>

Mem *last_link = NULL;

typedef struct _file_line
{
    char *file;
    long line;
    struct _file_line *prev;
    long total_allocs;

} file_line;

void *Malloc(size_t size, char *filename, long line_number)
{
    Mem *ml = (Mem *) malloc(sizeof(Mem));
    
    void *memory  = malloc(size);
    ml->address   = memory;
    ml->size      = size;
    ml->filename  = filename;
    ml->line      = line_number;
    ml->prev      = last_link;
    ml->next      = NULL;

    if (last_link == NULL)
    {
        last_link = ml;
    }
    else
    {
        last_link->next = ml;
        last_link = ml;

    }

    return memory;
}

void *Calloc(size_t size, size_t number, char *filename, long line_number)
{
    Mem *ml = (Mem *)malloc(sizeof(Mem));

    void *memory = calloc(size, number);
    ml->address  = memory;
    ml->size     = size*number;
    ml->filename = filename;
    ml->line     = line_number;
    ml->prev     = last_link;
    ml->next     = NULL;

    if (last_link == NULL)
    {
        last_link = ml;
    }
    else
    {
        last_link->next = ml;
        ml->prev = last_link;
        last_link = ml;
    }

    return memory;
}

void Free(void *memblock, char *filename, long line_number)
{
    Mem *ml = last_link;
    Mem *p,*n;
    int freed = 0;

    while(ml)
    {

        if (ml->address == memblock)
        {
            p = ml->prev;
            n = ml->next;

            if ((p == NULL) && (n == NULL))
            {
                // no more memory blocks will exist
                last_link == NULL;
            }
            else
            {
                if (p != NULL)
                {
                    p->next = n;
                } else
                    n->prev = NULL;
                
                if (n != NULL)
                {
                    n->prev = p;
                } else
                    p->next = NULL;
            }
            
            
            if (ml == last_link)
            {
                if ((p == NULL) && (n == NULL))
                    last_link = NULL;
                else
                {
                    if (p == NULL)
                    {
                        last_link = n;
                    }
                    else
                    {
                        last_link = p;
                    }
                }
            }

            free(ml);
            free(memblock);

            freed = 1;
            break;
        } else
        {
            ml = ml->prev;
        }
    }
    if (freed == 0)
    {
        printf("Free without alloc %s %ld\n", filename, line_number);
    }

}


/*
  Display all the memory allocations that haven't been freed
*/

void mem_list()
{
    Mem *ml = last_link;

    printf("-------------\n");
    if (ml == NULL)
    {
        printf("No memory allocated\n");
    }
    else
    {

        printf("filename\tline\taddress\t\tallocated\n");
        while (ml)
        {
            printf("%s\t%ld\t%p\t%ld\n", ml->filename, ml->line, ml->address, ml->size);

            ml = ml->prev;
        }
    }

    printf("Done.\n");
}

/*
  Display any allocations that were not freed
  but list them on the file and line number they were allocated
  with the number of times they were allocated.

*/

void mem_list_by_file_and_line()
{
    Mem *ml = last_link;
    char *file;
    long line;
    int found = 0;

    file_line *fl = NULL;
    file_line *f1 = NULL;
    file_line *nl = NULL;
    file_line *ll = NULL;


    printf("-------------\n");
    if (ml == NULL)
    {
        printf("No memory allocated\n");
    }
    else
    {
        fl = malloc(sizeof(file_line));
        fl->prev = NULL;

        fl->file = last_link->filename;
        fl->line = last_link->line;
        fl->total_allocs = 0;

        while (ml)
        {
            file = ml->filename;
            line = ml->line;

            found = 0;

            ll = fl;
            while (ll)
            {
                if ((file == ll->file) && (line == ll->line))
                {
                    ll->total_allocs++;
                    found = 1;
                    break;
                }
                ll = ll->prev;
            }

            // add
            if (found == 0)
            {
                nl = malloc(sizeof(file_line));
                nl->prev = fl;

                nl->file = file;
                nl->line = line;
                nl->total_allocs = 1;

                fl = nl;
            }

            ml = ml->prev;

        }

        printf("filename\tline\t# unfreed allocatons\n");

        while (fl)
        {
            printf("%s\t%ld\t%ld\n", fl->file, fl->line, fl->total_allocs);

            fl = fl->prev;
        }
    }

    printf("Done.\n");
}
