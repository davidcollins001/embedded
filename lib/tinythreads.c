
#include <embed/tinythreads.h>

// NOTE: this might not be needed with newer cython
struct thread_block threads[NTHREADS];
struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

//static
uint8_t initialised = 0;

static void initialise(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

    initialised = 1;
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
        // TODO: restart
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        printf("hello %p \n", current);
        longjmp(next->context, 1);
    }
}

void spawn(void (*function)(uint16_t), uint16_t arg) {
    thread newp;

    DISABLE();
    if (!initialised)
        initialise();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        printf("resume\n");
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
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
        printf("2");
        enqueue(current, &m->waitQ);
        thread t = m->waitQ;
        while(t) {
            printf("123 t %d\n", t->arg);
            printf("---%p\n", t->next);
            t = t->next;
        }
        // dispatch(dequeue(&readyQ));
        t = dequeue(&readyQ);
        printf(">> %p\n", t);
        dispatch(t);
    } else {
        m->locked = 1;
    }
    printf("\n");
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
