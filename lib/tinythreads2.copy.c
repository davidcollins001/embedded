
#include<setjmp.h>
#include<stdio.h>
#include<stdlib.h>

#include<tinythreads.h>

#define STACKDIR - // set to + for upwards and - for downwards

static int count = 0;

static char *tos; // top of stack
static void *coarg;

struct thread_block threads[NTHREADS];
struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

//static
uint8_t initialised = 0;


void display_q(thread *q) {
    int i = 0;
    thread t = *q;
    printf("==========vv==========\n");
    // printf(" %d) %p %d %p\n", i, t, t->arg, &initp);
    while(t) {
        printf(" %d) %p %d %p\n", ++i, t, t->arg, t->next);
        t = t->next;
    }
    printf("==========^^==========\n");
}

static void initialise(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

    initialised = 1;
}

static void enqueue(thread p, thread *queue) {
    printf("queue %p\n", p);
    display_q(queue);
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
        {
            // printf("enqueue %p\n", q);
            q = q->next;
        }
        q->next = p;
    }
    display_q(queue);
}

static thread dequeue(thread *queue) {
    printf("deque %p\n", *queue);
    thread p = *queue;
    display_q(queue);
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
        // TODO: restart
    }
    display_q(queue);
    p->next = NULL;
    return p;
}

void *dispatch(thread next) {
    if (setjmp(current->context))
        return 0;

    current = next;
    longjmp(next->context, 1);
}


void *spawn(void (*fun)(uint16_t), uint16_t arg) {

    DISABLE();
    if (!initialised)
        initialise();

    printf("*initp %p\n", &initp);

    if (tos == NULL)
        tos = (char*)&arg;

    tos += STACKDIR STACKSIZE;
    char stack[STACKDIR (tos - (char*)&arg)];
    coarg = stack;  // ensure optimizer keeps n

    current = dequeue(&freeQ);
    current->function = fun;
    current->arg = arg;
    current->next = NULL;
    current->stack = tos;

    count++;
    // current = &thread[count++];

    if (setjmp(initp.context))
        return(coarg);

    ENABLE();
    fun(arg);
    //abort();
}


void sched(void) {
    // schedule thread to run - needs to be run from main thread
    static int n = 0;
    n = n % (count - 1) + 1;
    dispatch(&thread[n], (char*)-1);

    enqueue(current, &readyQ);
    dispatch(dequeue(&readyQ));
}


void yield(void) {
    // switch to main thread to schedule another thread
    dispatch(&initp);
    printf("top\n");
    // sched();
}


void test(uint16_t arg) {
    int j = 0;

    while(1) {
        printf("coroutine %d at %p: %d\n", arg, current->arg, j++);
        yield();
    }
}


int main(void) {
    uint16_t i = 0;
    for(i=0; i<3; i++) {
        printf("spawning %d\n", count);
        fflush(stdout);
        spawn(test, i);
        printf("done\n");
        i++;
    }

    printf("\nschedule:\n");

    while(1)
        sched();

    return 0;
}

