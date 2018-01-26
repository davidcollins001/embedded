
#include <embed/tinythreads.h>

// NOTE: this might not be needed with newer cython
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

static void enqueue(thread p, thread *queue);

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

static void dispatch(thread next) {
    if (SETJMP(current->context) == 0) {
        printf("dispatch (%d)  %p -> %p\n", current->arg, current, next);
        current = next;
        printf("dispatching %p (%d) %p\n", next, next->arg, current);
        LONGJMP(next->context, 1);
    }
    printf("dispatched %p\n", current);
}

static unsigned int *tos;

void spawn(void (*function)(uint16_t), uint16_t arg) {
    thread newp;

    DISABLE();
    if (!initialised)
        initialise();
    printf("*initp %p\n", &initp);

    if(tos == NULL)
        tos = (void*)&arg;
    tos += STACKDIR STACKSIZE;

    // initp.next = readyQ;
    // readyQ = &initp;
    // display_q(&readyQ);

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    newp->stack = tos;
    // current = newp;
    current = &initp;
    if (SETJMP(newp->context) == 1) {
    // if (SETJMP(initp.context) == 0) {
        // printf("resume (%d)\n", current->arg);
        ENABLE();

        printf("__>> %p %p\n", &initp, &readyQ);

        current->function(current->arg);
        // printf("=====unreachable\n");
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    printf("********************\n");

    // SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
    ENABLE();
}

void yield(void) {
    printf("yielding\n");
    enqueue(current, &readyQ);
    thread t = dequeue(&readyQ);
    dispatch(t);
    printf("reentering %p\n", current);
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
        // printf("add to mutex q\n");
        enqueue(current, &m->waitQ);
        // vvvvvv debugging vvvvvv
        thread t = m->waitQ;
        while(t) {
            // printf("123 t (%d) %p\n", t->arg, t);
            // printf("---%p\n", t->next);
            t = t->next;
        }
        // ^^^^^^ debugging ^^^^^^
        // dispatch(dequeue(&readyQ));
        t = dequeue(&readyQ);
        // printf(">> %d\n", t->arg);
        dispatch(t);
    } else {
        // printf("locking\n");
        m->locked = 1;
    }
    ENABLE();
}

void unlock(mutex_t *m) {
    DISABLE();
    if(m->waitQ) {
        dispatch(dequeue(&m->waitQ));
    } else  {
        m->locked = 0;
    }
    ENABLE();
}
