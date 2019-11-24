#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "typedefine.h"
#include "config.h"

LIST_HEAD(queuehead, queue_entry) ready_queue_head;
struct queue_entry
{
    task_const_type task;
    LIST_ENTRY(queue_entry) queue_entries;
};

status_type activate_task(task_type id);
status_type terminate_task(void);

#endif /* TASK_H */
