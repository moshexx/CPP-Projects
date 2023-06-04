/******************************************************************************/
/*		Descriptions - UID API Functions v3									  */
/*		Date: 9.11.2020					    								  */
/*		Group: OL96						    								  */
/******************************************************************************/

#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h>
#include <time.h> 

typedef struct uid
{
    time_t time_stamp;
    pid_t pid;
    size_t counter;
}ilrd_uid_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* 
* Description: Creates a uid
* Return value: a newly created struct uid (ilrd_uid_t)
* Errors: Returns a "bad" uid if one of the fields failed
* Undefined behavior: none.
*	      			
* Complexity: O(1)
*/
ilrd_uid_t UIDCreate(void);

/* 
* Description: checks if one and other are identical
* Return value: 1(TRUE) if they are, 0(FALSE) else
* Errors: none.
* Undefined behavior: none.
*	      			
* Complexity: O(1)
*/
int UIDIsSame(ilrd_uid_t one, ilrd_uid_t other);

/* 
* Description: creates an instance of bad uid for comparison
* Return value: a bad uid
* Errors: none.
* Undefined behavior: none.
*	      			
* Complexity: O(1)
*/
ilrd_uid_t UIDGetBadUID(void);

#endif   /*__UID_H__*/