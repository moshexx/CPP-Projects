/*******************************************************************************
*		Descriptions - watchdog_api API Function                               *
*       author: Moshe Cohen	                                                   *
*		Date:  5.1.2020						                                   *
*		Group: OL96							                                   *
*******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SYNOPSIS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Description:
WatchDog is A program that Provides protection for an essential piece of code.
Since WD is activated until its completion -
the process within the framework of the essential code section is protected,
this means that if the process stops for any reason,
the WatchDog program re-runs it.

The method:
Mutual Protection - The process of the WatchDog watches the vital process,
and vice versa.
This ensures optimal protection.

Weak spots:
* If both processes stop at the same time -
  the WatchDog will NOT be able to run the essential program again.
* If one of the processes stops - there is a vulnerable short period which
  there is no backup to the program that is still running.

use instructions:
The function WatchDogStart should be called before beginning the critical code section.
The function WatchDogStop should be called at the end of the critical code section.

Remarks:
SIGUSR1 and SIGUSR2 signals must not be used in the essential code section,
because the WatchDog uses them for communication between processes.
*/

#ifndef __WATCHDOG_API__
#define __WATCHDOG_API__

#include <time.h> /* time_t */

typedef enum
{
    USER_APP,
    WD
}sender_t;

enum status_t
{
    SUCCESS = 0,
    FAILURE = 1,
    ALLOCATION_FAILURE = 2
};

/*
* Description:  @send_frequency is the frequency of sending life signal from each
                process to another.
                @check_frequency is the frequency of checking if any life signal
                recived from the other process.
                @sender must be set as USER_APP!
* Return value: according status_t: SUCCESS, FAILURE or ALLOCATION_FAILURE.
* Errors: none
* Undefined behavior: @sender must be set as USER_APP!
                      @send_frequency must be greater than @check_frequency.
                      use with SIGUSR1 & SIGUSR2 in vital section is not allowed.
* Complexity:
*/
int WatchDogStart(sender_t sender, time_t send_frequency, time_t check_frequency,
                                 int argc,char **argv, char *path_name_watchdog);

/*
* Description:
* Return value: none
* Errors: none
* Undefined behavior: WatchDogStop must be called after WatchDogStart.
* Complexity:
*/
void WatchDogStop(void);


#endif   /* __WATCHDOG_API__ */
