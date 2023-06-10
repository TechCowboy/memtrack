#include <stddef.h>
#ifdef MEMTRACK_ON

	typedef struct _Mem
	{
		size_t  size;
        char    *filename;
        long    line;
        void    *address;
		struct _Mem	*next;
		struct _Mem	*prev;
	} Mem;

extern void *Malloc(size_t size, char *filename, long line_number);
extern void *Calloc(size_t size, size_t number, char *filename, long line_number);
extern void Free(void *memblock, char *filename, long line_number);
extern void mem_list();
extern void mem_list_by_file_and_line();

#define MT_Malloc(size)          Malloc(size, __FILE__, __LINE__)
#define MT_Calloc(size, number)  Calloc(size, number, __FILE__, __LINE__)
#define MT_Free(address)         Free(address, __FILE__, __LINE__)


#else
	#define MT_Malloc(size) malloc(size)
	#define MT_Calloc(size) calloc(size, number)
	#define MT_Free(addess) free(address)
#endif