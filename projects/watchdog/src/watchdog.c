/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: watchdog.c
*	author: Moshe Cohen
*	reviewer: Ben Ronen

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
#include <stdlib.h>		/* getenv(), setenv() */
#include <assert.h> 	/* assert */
#include <unistd.h>  	/* sleep() */

#include "watchdog_api.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main(int argc, char *argv[], char *envp[])
{
	time_t frequency_send = atoi(getenv("SEND_FREQUENCY"));
	time_t frequency_check = atoi(getenv("CHECK_FREQUENCY"));

	WatchDogStart(WD, frequency_send, frequency_check, argc, argv,
		 										getenv("WD_PATH"));

	(void)envp;

	return SUCCESS;
}
