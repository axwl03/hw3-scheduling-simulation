#include "task.h"

status_type activate_task(task_type id)
{
    /* check whether task is in ready queue */
    struct queue_entry *np;
    for(np = ready_queue_head.tqh_first; np != NULL; np = np->queue_entries.tqe_next)
    {
        if(np->task.id == id)
        {
            return STATUS_ERROR;
        }
    }
    if(running->task.id == id)
    {
        return STATUS_ERROR;
    }

    /* insert task into ready queue */
    np = malloc(sizeof(struct queue_entry));
    if(np == NULL)
    {
        printf("malloc failed\n");
        exit(1);
    }
    np->task = task_const[id];
    np->context_p = NULL;
    TAILQ_INSERT_TAIL(&ready_queue_head, np, queue_entries);
    swapcontext(running->context_p, &schedular_context);
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
    running = NULL;
    return STATUS_OK;
}
