
#include <embed/rtos.h>

#include <stdio.h>

/*
 * TODO:
 *  - both tasks run at the same time
 *  - add ability to selecte priority when adding task
 */

static uint8_t rtos_initialised = 0;

void idle_task(void) {
#ifdef DEBUG
    printf("Running idle task, entering sleep");
#endif
    sleep_now(SLEEP_MODE_PWR_DOWN);
}

void debug_run1(void) {
    PORTC ^= 1;
}

void debug_run2(void) {
    PORTC ^= 2;
}

void init_rtos(uint8_t rate) {
    uint8_t i;
    tasks_num = 0;

    // set timer to interrupt ever 1/8 s
    init_timer(rate, WDT);

    // ensure task list is empty
    for(i=MAX_TASKS; i; i--) {
        task_list[i].id = 0;
        task_list[i].task = (task_t)0x0;
        task_list[i].delay = 0;
        task_list[i].period = 0;
        task_list[i].status = STOPPED;
    }
    rtos_initialised = 1;

    // put idle task as first task
    add_task(idle_task, 0);

    PORTC = 0;
}

void add_task(task_t task, uint8_t period) {
    tcb_t *t;

    if(rtos_initialised && (tasks_num <= MAX_TASKS)) {
        t = &task_list[tasks_num];

        t->id = tasks_num;
        t->task = task;
        t->delay = period;
        t->period = period;
        t->status = READY;
        tasks_num++;
    }
}

void sched(void) {
    /*
     * run all processes sequentially from highest to lowest
     * with id=1 being the idle process
     */
    uint8_t i;
    tcb_t *task;

    // check rtos has been initialised
    assert(rtos_initialised);

    // scheduler - run all processes sequentially
    for(i=tasks_num; i; i--) {
        task = &task_list[i-1];
        if(task->period)
            task->delay--;
        if((!task->delay) && (task->status == READY)) {
#ifdef DEBUG
            printf("running task: %d\n", i-1);
#endif
            task->status = RUNNING;
            (*task->task)();
            task->delay = task->period;
            task->status = READY;
        }
    }
}

// should be in test program
int run(void) {
    init_rtos(3);

    add_task(debug_run1, (uint8_t)8);
    add_task(debug_run2, (uint8_t)4);

    while(true) {
        sched();

#ifdef TEST
        return 1;
#endif
    }

    return 0;
}

/*
#ifndef TEST
int main(void) {
    run();
}
#endif
*/

