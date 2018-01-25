
#include <assert.h>
#include <embed/tinythreads.h>

mutex_t m;

void task1(uint16_t arg) {

    while(1) {
        printf("running task1 %p %d\n", current, arg);
        // lock(&m);
        // yield to second thread to block on mutex
        yield();
        printf("resumed: %p\n", current);
        printf("unlock\n");
        // unlock(&m);
    }
}

void task2(uint16_t arg) {
    while(1) {
        printf("running task2 %p %d\n", current, arg);
        // lock(&m);
        // should be blocked waiting for mutex
        printf("shouldn't get here\n");
        yield();
        printf("resumed: %p\n", current);
    }
}

void task3(uint16_t arg) {
    while(1) {
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

    printf(" 0) %d\n", initp.arg);
    for(i=0; i<4; i++)
        printf(" %d) %d\n", i+1, threads[i].arg);

    i = 0;
    printf(" %d) %p %d %p\n", i, initp, initp.arg, initp.next);
    while(t) {
        printf(" %d) %p %d %p\n", ++i, t, t->arg, &threads[i]);
        t = t->next;
    }

    // while(1) {
        printf("* in main\n");
        yield();
        printf("* completed yield\n");
        printf("resumed: %p\n", current);
    // }

        display_q(&readyQ);
        yield();

    return 0;
}

void runner(uint16_t arg) {
    while(1) {
        printf("in runner: %d\n", arg);
        display_q(&readyQ);
        yield();
    }
}

int run2(void) {
    spawn(runner, 1);
    spawn(runner, 2);

    display_q(&readyQ);
}


int main(void) {

    printf("---> sp = %p %p\n", 1, 2);
    // printf("---> sp = %p %p\n", current->context[8], current->context->_jb[0]);

    run1();
    // run2();

    return 0;
}
