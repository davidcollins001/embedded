
#ifndef RTOS_H_
#define RTOS_H_

#include <inttypes.h>

#define MAX_TASK 5

typedef volatile uint8_t (*task_fn_t)(void *args);

typedef struct {
    task_fn_t task_fn;
} task_t;

task_t task_list[MAX_TASK];

void add_task();

#endif //RTOS_H_

