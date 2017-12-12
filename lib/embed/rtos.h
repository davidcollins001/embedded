
#ifndef RTOS_H_
#define RTOS_H_

#include <inttypes.h>

#include <avr/io.h>

#include <embed/sleep.h>
#include <embed/interrupt.h>

#define MAX_TASKS 5
#define NULL ( (void *) 0)

typedef void (*taskfn_t)(void);

typedef struct {
    uint8_t id;
    taskfn_t task_fn;
} task_t;

task_t task_list[MAX_TASKS+1];
uint8_t tasks_num;

void init_tasks(void);
void add_task(taskfn_t task);
void sched(void);

#endif //RTOS_H_

