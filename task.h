#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "typedefine.h"
#include "config.h"

extern int resource_owner[RESOURCES_COUNT];
extern struct queue_entry *running;
extern struct queuehead ready_queue_head;
extern ucontext_t schedular_context;
status_type activate_task(task_type id);
status_type terminate_task(void);

#endif /* TASK_H */
