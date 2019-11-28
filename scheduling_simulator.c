#include "resource.h"
#include "task.h"
#include <ucontext.h>
#define MEM 8192

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
        TAILQ_INSERT_HEAD(&ready_queue_head, np, queue_entries);
    }

    /* schedule and run */
    while(1)
    {
        schedule_task();
        if(running->context_p == NULL)
        {
            running->context_p = malloc(sizeof(ucontext_t));
            if(running->context_p == NULL)
            {
                printf("malloc failed\n");
                exit(1);
            }
            getcontext(running->context_p);
            running->context_p->uc_stack.ss_sp = malloc(MEM);
            running->context_p->uc_stack.ss_size = MEM;
            running->context_p->uc_link = &schedular_context;
            makecontext(running->context_p, running->task.entry, 0);
            swapcontext(&schedular_context, running->context_p);
        }
        else
        {
            setcontext(running->context_p);
        }
    }
    return 0;
}

void schedule_task()
{
    struct queue_entry *np, *max_priority_np;
    if(running == NULL)
        max_priority_np = ready_queue_head.tqh_first;
    else
        max_priority_np = running;
    for(np = ready_queue_head.tqh_first; np != NULL; np = np->queue_entries.tqe_next)
        if(np->task.static_priority > max_priority_np->task.static_priority)
            max_priority_np = np;
    if(running != NULL)
        TAILQ_INSERT_HEAD(&ready_queue_head, running, queue_entries);
    TAILQ_REMOVE(&ready_queue_head, max_priority_np, queue_entries);
    running = max_priority_np;
}
