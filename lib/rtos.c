
#include <embed/rtos.h>


void init(void) {
    uint8_t i;

    for(i=MAX_TASKS; i>0; i--)
        task_list[i] = (task_t)NULL;

    PORTC = 0;
}


uint8_t idle_task(void *none) {
    sleep();
}


uint8_t run1(void *none) {
    PORTC ^= 1;
}


uint8_t run2(void *none) {
    PORTC ^= 2;
}


void add_task(task_t task) {
    if(tasks == 0) {
        // insert idle/sleep task at end
        task_t idle = {&idle_task};
        task_list[MAX_TASKS] = idle;
        tasks++;
    }
    if(tasks < MAX_TASKS) {
        task_t idle = {task};
        tasks++;
    }
}

    //
// ------- 8< -------

int main(void) {
    uint8_t i;
    taskfn_t func;

    init();

    add_task(&run1);
    add_task(&run2);

    while(true) {

        // scheduler
        // run all processes secuentially
        for(i=MAX_TASKS; i>0; i--) {
            if(task_list[i]) {
                func = task_list[i].taskfn;
                func(NULL)
            }
        }
    }

}

