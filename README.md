# memtrack

Keeps track of c allocations in a link list.  Let's you know 
* where you forgot to free by listing file and line number
* freed something that wasn't allocated

```
./test

Free without alloc src/main.c 25
-------------
filename        line    address         allocated
src/main.c      19      0x55e436bbc090  2000
src/main.c      19      0x55e436bbb870  2000
src/main.c      19      0x55e436bbb050  2000
src/main.c      19      0x55e436bba830  2000
src/main.c      19      0x55e436bba010  2000
src/main.c      19      0x55e436bb97f0  2000
src/main.c      19      0x55e436bb8fd0  2000
src/main.c      19      0x55e436bb87b0  2000
src/main.c      19      0x55e436bb7f90  2000
src/main.c      19      0x55e436bb7770  2000
src/main.c      19      0x55e436bb6f50  2000
src/main.c      19      0x55e436bb6730  2000
src/main.c      19      0x55e436bb5f10  2000
src/main.c      19      0x55e436bb56f0  2000
src/main.c      19      0x55e436bb4ed0  2000
src/main.c      19      0x55e436bb46b0  2000
src/main.c      19      0x55e436bb3e90  2000
src/main.c      19      0x55e436bb3670  2000
src/main.c      19      0x55e436bb2e50  2000
src/main.c      14      0x55e436bb29b0  512
src/main.c      14      0x55e436bb2760  512
src/main.c      14      0x55e436bb2510  512
src/main.c      14      0x55e436bb22c0  512
src/main.c      14      0x55e436bb2070  512
src/main.c      14      0x55e436bb1e20  512
src/main.c      14      0x55e436bb1bd0  512
src/main.c      14      0x55e436bb1980  512
src/main.c      14      0x55e436bb1730  512
Done.
-------------
filename        line    # unfreed allocatons
src/main.c      14      9
src/main.c      19      19
Done.
```
