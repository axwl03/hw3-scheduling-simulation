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
    // need scheduling decision
    return STATUS_OK;
}

status_type terminate_task(void)
{
    /* check whether calling task still occupies resource */
    for(int i = 0; i < RESOURCES_COUNT; ++i)
        if(resource_owner[i] == running->task.id)
            return STATUS_ERROR;

    /* terminate calling task */
    free(running);
    // need scheduling decision
    return STATUS_OK;
}
