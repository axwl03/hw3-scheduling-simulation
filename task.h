#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h>
#include "typedefine.h"
#include "config.h"

extern struct queuehead ready_queue_head;
status_type activate_task(task_type id);
status_type terminate_task(void);

#endif /* TASK_H */
