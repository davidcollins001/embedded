
#include<setjmp.h>
#include<stdio.h>
#include<stdlib.h>

#include<embed/tinythreads.h>

// NOTE: this might not be needed with newer cython
struct thread_block threads[NTHREADS];
struct thread_block scheduler;
struct thread_block mainp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &scheduler;

//static
uint8_t initialised = 0;

static uint8_t *tos; // top of stack
static void *coarg;


void display_q(thread *q) {
    int i = 0;
    thread t = *q;
    printf("==========vv==========\n");
    // printf(" %d) %p %d %p\n", i, t, t->arg, &scheduler);
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

    scheduler.next = NULL;
    mainp.next = NULL;

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
        while (1)
            printf("spin\n");  // not much else to do...
        // TODO: restart
    }
    display_q(queue);
    p->next = NULL;
    return p;
}

void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context, 1);
    }
}

void spawn(void (*function)(uint16_t), uint16_t arg) {
    DISABLE();
    if (!initialised)
        initialise();
    printf("*scheduler %p\n", &scheduler);
    printf("*mainp %p\n", &mainp);

    if (tos == NULL)
        tos = (uint8_t*)&arg;

    current = dequeue(&freeQ);

    tos += STACKDIR STACKSIZE;
    uint8_t stack[STACKDIR (tos - (uint8_t*)&arg)];
    current->stack = stack; // ensure optimizer keeps stack
    current->function = function;
    current->arg = arg;

    // if (setjmp(scheduler.context) == 0) {
    if (setjmp(current->context) == 1) {
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
    // scheduler process dispatches to a process, all other process
    // pass off to scheduler process to schedule a new process
    // if(current == &scheduler){
        // dispatch(dequeue(&readyQ));
    // } else {
        // enqueue(current, &readyQ);
        // dispatch(&scheduler);
    // }
    thread t = dequeue(&readyQ);
    enqueue(current, &readyQ);
    dispatch(t);
}


void lock(mutex_t *m) {
    DISABLE();
    if(m->locked) {
        // printf("add to mutex q\n");
        enqueue(current, &m->waitQ);
        // vvvvvv debugging vvvvvv
        thread t = m->waitQ;
        while(t) {
            printf("123 t (%d) %p\n", t->arg, t);
            // printf("---%p\n", t->next);
            t = t->next;
        }
        // ^^^^^^ debugging ^^^^^^
        // dispatch(dequeue(&readyQ));
        // t = dequeue(&readyQ);
        // printf(">> %d\n", t->arg);
        // dispatch(t);
        // yield();
        dispatch(dequeue(&readyQ));
    } else {
        printf("locking\n");
        m->locked = 1;
    }
    ENABLE();
}

void unlock(mutex_t *m) {
    DISABLE();
    if(m->waitQ) {
        dispatch(dequeue(&m->waitQ));
    } else  {
        printf("unlocking\n");
        m->locked = 0;
    }
    ENABLE();
}


int j = 0;
mutex_t m;
static void runner1(uint16_t arg) {
    lock(&m);
    printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
    unlock(&m);
    yield();

     while(1) {
        printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
        yield();
    }
}

static void runner2(uint16_t arg) {
    printf("enter2\n");
    lock(&m);
    printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
    unlock(&m);
    yield();

    while(1) {
        printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
        yield();
    }
}

static void runner3(uint16_t arg) {
    while(1) {
        printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
        yield();
    }
}

int main(void) {
    printf("spawning %d\n", 1);
    spawn(runner1, 1);
    printf("spawning %d\n", 2);
    spawn(runner2, 2);
    printf("spawning %d\n", 3);
    spawn(runner3, 3);

    printf("\nschedule:\n");

    while(1) {
        printf("*main\n");
        yield();
    }

    return 0;
}

