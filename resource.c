#include "resource.h"

status_type get_resource(resource_type id)
{
    if(resource_owner[id] == 0) 		// not occupied
    {
        resource_owner[id] = running->task.id;
        if(running->task.static_priority < resources_priority[id])
            running->task.static_priority = resources_priority[id];
        return STATUS_OK;
    }
    else return STATUS_ERROR;			// occupied
}

status_type release_resource(resource_type id)
{
    if(resource_owner[id] == running->task.id) 	// occupied by the calling task
    {
        resource_owner[id] = 0;
        running->task.static_priority = task_const[running->task.id].static_priority;
        // need scheduling decision
        return STATUS_OK;
    }
    else return STATUS_ERROR;		// not occupied by the calling task
}
