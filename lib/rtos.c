
#include <embed/rtos.h>


void init_tasks(void) {
    // uint8_t i;
    tasks_num = 0;

    // for(i=MAX_TASKS; i>0; i--)
        // task_list[i] = (task_t)NULL;

    PORTC = 0;
}


void idle_task(void) {
    // sleep_now(SLEEP_MODE_PWR_DOWN);
}


void run1(void) {
    PORTC ^= 1;
}


void run2(void) {
    PORTC ^= 2;
}


void add_task(taskfn_t task) {

    // put idle task as first task
    if(tasks_num == 0) {
        task_t idle = { 0, idle_task };
        // *idle.task_fn = &idle_task;
        task_list[0] = idle;
        tasks_num++;
    }

    if(tasks_num < MAX_TASKS) {
        task_t idle = { tasks_num, task};
        task_list[tasks_num] = idle;
        tasks_num++;
    }
    printf("%d\n" ,tasks_num);
}

void sched(void) {
    uint8_t i;
    printf("%d\n" ,tasks_num);
    // TODO: fix: tasks_num is 0 here, should be 2

    // scheduler - run all processes secuentially
    // for(i=tasks_num; i; i--) {
    for(i=0; i<tasks_num; i--) {
    printf("%d\n" ,3);
        printf("running task %d\n", i);
        task_list[i].task_fn();
    }
}

// ------- 8< -------

int main(void) {
    init_tasks();

    add_task(run1);
    add_task(run2);

    while(true) {
        sched();

#ifdef TEST
        return 1;
#endif
    }

    return 0;
}

