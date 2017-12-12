
#ifndef RTOS_H_
#define RTOS_H_

#include <inttypes.h>

#include <avr/io.h>

#include <embed/sleep.h>
#include <embed/interrupt.h>

#define MAX_TASKS 5
#define NULL ( (void *) 0)

typedef volatile uint8_t (*taskfn_t)(void *args);

typedef struct {
    taskfn_t task_fn;
} task_t;

task_t task_list[MAX_TASKS+1];
uint8_t tasks = 0;

void init_tasks(void);
void add_task(task_t task);

#endif //RTOS_H_

