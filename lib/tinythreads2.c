
#include<setjmp.h>
#include<stdio.h>
#include<stdlib.h>

#define STACKDIR - // set to + for upwards and - for downwards
#define STACKSIZE (1<<12)
#define MAXTHREAD 10000

static jmp_buf thread[MAXTHREAD];
static int count = 0;

static char *tos; // top of stack
static void *coarg;
static jmp_buf *current = &thread[0];


void *dispatch(jmp_buf *next, void *arg) {
    coarg = arg;

    if (setjmp(*current))
        return(coarg);

    current = next;
    longjmp(*next, 1);
}


void *spawn(void (*fun)(int), int arg) {
    if (tos == NULL) tos = (char*)
        &arg;

    tos += STACKDIR STACKSIZE;
    char n[STACKDIR (tos - (char*)&arg)];
    coarg = n; // ensure optimizer keeps n

    current = &thread[++count];

    if (setjmp(thread[0]))
        return(coarg);

    fun(arg);
    //abort();
}

void sched(void) {
    static int n = 0;
    n = n % (count - 1) + 1;
    dispatch(&thread[n], (char*)-1);
}

void yield(void) {
    dispatch(&thread[0], (char*)1);
    // sched();
}

static void comain(int arg) {
    int j = 0;

    while(1) {
        printf("coroutine %d at %p: %d\n", arg, (void*)&thread[arg], j++);
        yield();
    }
}

int main(void) {
    int i = 0;
    while (++i < 6) {  // MAXTHREAD) {
        printf("spawning %d\n", count+1);
        spawn(comain, i);
    }

    printf("schedule:\n");

    while(1)
        sched();

    return 0;
}

