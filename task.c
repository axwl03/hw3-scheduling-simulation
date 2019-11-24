#include "task.h"

status_type activate_task(task_type id)
{
    /* check whether task is in ready queue */
    struct queue_entry *np;
    for(np = ready_queue_head.lh_first; np != NULL; np = np->queue_entries.le_next)
        if(np->task.id == id)
            return STATUS_ERROR;

    /* insert task into ready queue */
    np = malloc(sizeof(struct queue_entry));
    if(np == NULL)
    {
        printf("malloc failed\n");
        exit(1);
    }
    np->task = task_const[id];
    LIST_INSERT_HEAD(&ready_queue_head, np, queue_entries);
    return STATUS_OK;
}

status_type terminate_task(void)
{
    status_type result = STATUS_OK;

    return result;
}
