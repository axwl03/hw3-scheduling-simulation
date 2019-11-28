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
    np->context_p = NULL;
    LIST_INSERT_HEAD(&ready_queue_head, np, queue_entries);
    if(running->context_p == NULL)
    {
        running->context_p = malloc(sizeof(ucontext_t));
        if(running->context_p == NULL)
        {
            printf("malloc failed\n");
            exit(1);
        }
    }
    printf("swap\n");
    printf("swapcontext ret: %d\n", swapcontext(running->context_p, &schedular_context));
    printf("return back\n");
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
