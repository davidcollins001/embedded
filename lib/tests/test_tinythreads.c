
#include <assert.h>
#include <embed/tinythreads.h>

mutex_t m;
int ii = 0;

void task1(uint16_t arg) {
    printf("running task1 %p\n", current);
    if(!ii) {
        lock(&m);
        // yield to second thread to block on mutex
        yield();
        ii = 1;
    }
    printf("unlock\n");
    unlock(&m);
}

void task2(uint16_t arg) {
    printf("running task2 %p\n", current);
    lock(&m);
    // should be blocked waiting for mutex
    printf("shouldn't get here\n");
}

void task3(uint16_t arg) {
    printf("running task3 %p\n", current);
    uint8_t count = 0;

    // check task2 is on waitQ in mutex
    thread t = m.waitQ;
    while(t) {
        printf("-> task: %p\n", t);
        count++;
        t = t->next;
    }

    assert(count == 1);
    printf("yield from 3\n");
    yield();
}

int main(void) {
    int i;
    thread t;

    spawn(task1, 0);
    spawn(task2, 1);
    spawn(task3, 2);

    t = readyQ;

    printf("tasks:\n");
    for(i=0; i<4; i++)
        printf(" %d) %d\n", i+1, threads[i].arg);

    i = 0;
    while(t) {
        printf(" %d) %p %d %p %p %d\n", ++i, t, t->arg,
            threads+i*sizeof(*threads), &threads[i],
            sizeof(threads));
        //(threads+i*sizeof(thread))->arg);
        t = t->next;
    }

    while(1) {
        printf("* in main\n");
        yield();
    }

    return 0;
}
