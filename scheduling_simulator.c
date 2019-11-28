#include "resource.h"
#include "task.h"
#include <ucontext.h>

int resource_owner[RESOURCES_COUNT];
struct queue_entry *running = NULL;
struct queuehead ready_queue_head;
ucontext_t schedular_context;

void schedule_task();

int main()
{
    /* initialization */
    for(int i = 0; i < RESOURCES_COUNT; ++i)
    {
        resource_owner[i] = 0;
    }

    /* auto start */
    struct queue_entry *np;
    for(int i = 0; i < AUTO_START_TASKS_COUNT; ++i)
    {
        np = malloc(sizeof(struct queue_entry));
        if(np == NULL)
        {
            printf("malloc failed\n");
            exit(1);
        }
        np->task = task_const[auto_start_tasks_list[i]];
        np->context_p = NULL;
        LIST_INSERT_HEAD(&ready_queue_head, np, queue_entries);
    }

    /* schedule and run */
    while(1)
    {
        getcontext(&schedular_context);
        schedule_task();
        printf("run T%d\n", running->task.id);
        if(running->context_p == NULL)
            (*(running->task.entry))();
        else
        {
            printf("jump back to T%d\n", running->task.id);
            setcontext(running->context_p);
        }
    }
    return 0;
}

void schedule_task()
{
    printf("schedule task\n");
    struct queue_entry *np, *max_priority_np;
    if(running == NULL)
        max_priority_np = ready_queue_head.lh_first;
    else
        max_priority_np = running;
    for(np = ready_queue_head.lh_first; np != NULL; np = np->queue_entries.le_next)
        if(np->task.static_priority > max_priority_np->task.static_priority)
            max_priority_np = np;
    if(running != NULL)
        LIST_INSERT_HEAD(&ready_queue_head, running, queue_entries);
    LIST_REMOVE(max_priority_np, queue_entries);
    running = max_priority_np;
}
