
#include <embed/tinythreads.h>

#ifdef TEST
#include<stdio.h>
#endif

// NOTE: this might not be needed with newer cython
struct thread_block threads[NTHREADS];
struct thread_block mainp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &mainp;

//static
uint8_t initialised = 0;

static uint8_t *tos; // top of stack
static void *coarg;


void display_q(thread *q) {
    int i = 0;
    thread t = *q;
    printf("==========vv==========\n");
    // printf(" %d) %p %d %p\n", i, t, t->arg, &mainp);
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

    mainp.next = NULL;

    initialised = 1;
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
        {
            q = q->next;
        }
        q->next = p;
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1)
            printf("spin\n");  // not much else to do...
        // TODO: restart
    }
    p->next = NULL;
    return p;
}

static void dispatch(thread next) {
    if (SETJMP(current->context) == 0) {
        current = next;
        LONGJMP(next->context, 1);
    }
}

void spawn(void (*function)(uint16_t), uint16_t arg) {
    DISABLE();
    if (!initialised)
        initialise();

    // put this here to find current top of stack
    if (tos == NULL)
        tos = (uint8_t*)&arg;

    current = dequeue(&freeQ);

    tos += STACKDIR STACKSIZE;
    uint8_t stack[STACKDIR (tos - (uint8_t*)&arg)];
    current->stack = stack; // ensure optimizer keeps stack
    current->function = function;
    current->arg = arg;

    if (SETJMP(current->context) == 1) {
        ENABLE();
        current->function(current->arg);

        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }

    enqueue(current, &readyQ);
    current = &mainp;

    //abort();
    ENABLE();
}

void yield(void) {
    enqueue(current, &readyQ);
    dispatch(dequeue(&readyQ));
}

#ifdef TEST
// yield intereferes with python yield so create test version
void t_yield(void) {
    yield();
}
#endif // TEST

void lock(mutex_t *m) {
    DISABLE();
    if(m->locked) {
        enqueue(current, &m->waitQ);
        dispatch(dequeue(&readyQ));
    } else {
        m->locked = 1;
    }
    ENABLE();
}

void unlock(mutex_t *m) {
    DISABLE();
    if(m->waitQ) {
        enqueue(current, &readyQ);
        dispatch(dequeue(&m->waitQ));
    } else  {
        m->locked = 0;
    }
    ENABLE();
}
