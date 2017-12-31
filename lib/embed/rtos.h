
#ifndef _RTOS_H_
#define _RTOS_H_

#include <inttypes.h>
#include <stddef.h>
#include <assert.h>

#include <avr/io.h>

#include <embed/sleep.h>
#include <embed/timer.h>

#define MAX_TASKS 5

#define READY 0x1
#define RUNNING 0x2
#define STOPPED 0x3
#define YIELD 0x4

typedef void (*task_t)(void);

typedef struct {
    uint8_t id;
    task_t task;
    uint8_t delay;
    uint8_t period;
    uint8_t status;
} tcb_t;

tcb_t task_list[MAX_TASKS+1];
uint8_t tasks_num;

void init_rtos(uint8_t rate);
void add_task(task_t task, uint8_t period);
void sched(void);

#endif //_RTOS_H_

