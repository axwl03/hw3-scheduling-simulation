#include "resource.h"
#include "task.h"


int main()
{
    printf("T1: %d\n", activate_task(T1));
    printf("T2: %d\n", activate_task(T2));
    struct queue_entry *np;
    for(np = ready_queue_head.lh_first; np != NULL; np = np->queue_entries.le_next)
        printf("%d\n", np->task.id);
//    while (1);
    return 0;
}
