/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: user_app.c
*	author: Moshe Cohen
*	reviewer: Ben Ronen

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 	/* assert */
#include <unistd.h>  	/* for sleep() */

#include "watchdog_api.h"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* compile (if all file in the same dir) */
/*
gc watchdog.c watchdog_api.c -I ../ds/include/ -I ../system_programming/include/ -Wl,-rpath=$PWD ds.so -lpthread -lm -o wd.out
gc user_app.c watchdog_api.c -I ../ds/include/ -I ../system_programming/include/ -Wl,-rpath=$PWD ds.so -lpthread -lm
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void UserApp(void);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main(int argc, char *argv[])
{
	size_t n = 4;
	char wd_path[] = "/home/moshe/git/projects/watchdog/bin/wd.out";

	WatchDogStart(USER_APP, 1, 2, argc, argv, wd_path);

	UserApp();
	WatchDogStop();

	while(n)
	{
		printf("User_App continue unprotectedly\n");
		sleep(1);
		--n;
	}
	(void)argc;
	(void)argv;

	return SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void UserApp(void)
{
	size_t n = 12;

	while(n)
	{
		printf("UserApp, %lu\n", n);
		--n;
		sleep(1);
	}
}
