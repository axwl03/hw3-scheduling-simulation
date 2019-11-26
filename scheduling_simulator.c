#include "resource.h"
#include "task.h"

int resource_owner[RESOURCES_COUNT];
struct queue_entry *running = NULL;
struct queuehead ready_queue_head;

int main()
{
    /* initialization */
    for(int i = 0; i < RESOURCES_COUNT; ++i)
        resource_owner[i] = 0;

    struct queue_entry *np;
    for(np = ready_queue_head.lh_first; np != NULL; np = np->queue_entries.le_next)
        printf("%d\n", np->task.id);
//    while (1);
    return 0;
}
