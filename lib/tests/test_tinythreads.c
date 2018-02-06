
#include <assert.h>
#include <embed/tinythreads.h>

mutex_t m;

void task1(uint16_t arg) {
    uint8_t rc = 3;

    while(rc--) {
        printf("running task1 %p %d\n", current, arg);
        lock(&m);
        // yield to second thread to block on mutex
        yield();
        printf("resumed: %p\n", current);
        printf("unlock\n");
        unlock(&m);
    }
}

void task2(uint16_t arg) {
    uint8_t rc = 3;

    while(rc--) {
        printf("running task2 %p %d\n", current, arg);
        lock(&m);
        // should be blocked waiting for mutex
        printf("shouldn't get here\n");
        unlock(&m);
        yield();
        printf("resumed: %p\n", current);
    }
}

void task3(uint16_t arg) {
    uint8_t rc = 3;

    while(rc--) {
        printf("running task3 %p %d\n", current, arg);
        uint8_t count = 0;

        // check task2 is on waitQ in mutex
        thread t = m.waitQ;
        while(t) {
            printf("-> task: %p\n", t);
            count++;
            t = t->next;
        }

        // assert(count == 1);
        printf("yield from 3\n");
        yield();
        printf("resumed: %p\n", current);
    }
}

int run1(void) {
    int i;
    thread t;

    spawn(task1, 1);
    spawn(task2, 2);
    spawn(task3, 3);

    t = readyQ;

    printf(" 0) %d\n", mainp.arg);
    for(i=0; i<4; i++)
        printf(" %d) %d\n", i+1, threads[i].arg);

    i = 0;
    printf(" %d) %p %d %p\n", i, &mainp, mainp.arg, mainp.next);
    while(t) {
        printf(" %d) %p %d %p\n", ++i, t, t->arg, &threads[i]);
        t = t->next;
    }

    while(readyQ) {
        printf("* in main\n");
        fflush(stdout);
        yield();
        printf("* completed yield\n");
        printf("resumed: %p\n", current);
    }

    return 0;
}

void runner(uint16_t arg) {
    uint8_t rc = 4;

    while(rc--) {
        printf("in runner: %d\n", arg);
        display_q(&readyQ);
        yield();
    }
}

int run2(void) {
    spawn(runner, 1);
    spawn(runner, 2);

    display_q(&readyQ);

    while(readyQ) {
        yield();
    }

    display_q(&readyQ);
    display_q(&freeQ);
}


uint8_t j = 0;
static void runner1(uint16_t arg) {
    uint8_t rc = 3;

    lock(&m);
    printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
    yield();
    unlock(&m);

     while(rc--) {
        printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
        yield();
    }
}

static void runner2(uint16_t arg) {
    uint8_t rc = 3;

    printf("enter2\n");
    lock(&m);
    printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
    unlock(&m);
    yield();

    while(rc--) {
        printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
        yield();
    }
}

static void runner3(uint16_t arg) {
    uint8_t rc = 3;

    while(rc--) {
        printf("coroutine %d at %p: %d\n", arg, (void*)&threads[arg-1], j++);
        yield();
    }
}

int run3(void) {
    uint8_t rc = 3;

    printf("spawning %d\n", 1);
    spawn(runner1, 1);
    printf("spawning %d\n", 2);
    spawn(runner2, 2);
    printf("spawning %d\n", 3);
    spawn(runner3, 3);

    printf("\nschedule:\n");

    while(readyQ) {
        printf("*main\n");
        yield();
    }

    return 0;
}


int main(void) {
    /* run 3 test cases sequentially */

    printf("RUNNING 1\n");
    run1();

    printf("RUNNING 2\n");
    run2();

    printf("RUNNING 3\n");
    run3();

    printf("freeQ:\n");
    display_q(&readyQ);
    printf("readyQ:\n");
    display_q(&readyQ);

    return 0;
}
