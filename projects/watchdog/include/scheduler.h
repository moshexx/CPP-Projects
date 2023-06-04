/******************************************************************************/
/*		Descriptions - Scheduler API Functions								  */
/*		Date: 11.11.2020					     						   	  */
/*		Group: OL96						      								  */
/******************************************************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>
#include "uid.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef	struct scheduler sched_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* 
* Description: creates a scheduler that prioritize tasks by time to execute
* Return value: pointer to the scheduler
* Errors: returns NULL if memory allocation failed
* Undefined behavior: none
*	      			
* Complexity: O(1).
*/
sched_t *SchedCreate(void);

/*
* Description: frees all memory associated with the schedule
* Return value: none
* Errors: none.
* Undefined behavior: shced can't be NULL
*	      			
* Complexity: O(n).
*/
void SchedDestroy(sched_t *sched);

/*
* Description: adds a new task to the scheduler
* Return value: uid of the new task
* Errors: returns "bad uid" if failed to create task
* Undefined behavior: sched can't be NULL, time_t arguments can't be negative.
*
* Complexity: O(1).
*/
ilrd_uid_t SchedAddTask(sched_t *sched, time_t time_to_execute, time_t frequency
								 , int(*oper_func)(void *params), void *params);

/*
* Description: finds and remove the task with the given uid
* Return value: none
* Errors: none
* Undefined behavior: sched can't be NULL
*	      			
* Complexity: O(n).
*/
void SchedRemoveTask(sched_t *sched, ilrd_uid_t uid);

/*
* Description: removes all tasks from the scheduler
* Return value: none
* Errors: none
* Undefined behavior: sched can't be NULL
*	      			
* Complexity: O(n).
*/
void SchedFlush(sched_t *sched);

/*
* Description: starts running and tasks in the scheduler. 
  Stops when there are no more tasks, one task failed, or if Stop was called
* Return value: 0 (SUCCESS) or 1 (FAILURE) if one task failed
* Errors: none
* Undefined behavior: sched can't be NULL
*	      			
* Complexity: O(n).
*/
int SchedRun(sched_t* sched);

/*
* Description: stop function to stop sched
* Return value: 0 (SUCCESS) (can't fail)
* Errors: none.
* Undefined behavior: sched can't be NULL
*	      			
* Complexity: O(1).
*/
int SchedStop(sched_t *sched);

/* 
* Description: checks if sched is empty
* Return value: 1 (TRUE) if it is, 0 (FALSE) else
* Errors: none
* Undefined behavior:  sched can't be NULL
*	      			
* Complexity: O(1).
*/
int SchedIsEmpty(sched_t* sched);

/* 
* Description: checks the size of sched
* Return value: number of tasks in sched
* Errors: none
* Undefined behavior: sched can't be NULL
*	      			
* Complexity: O(1).
*/
size_t SchedSize(sched_t* sched);

#endif   /*__SCHEDULER_H__*/
