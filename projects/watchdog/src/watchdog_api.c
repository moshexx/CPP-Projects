/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: watchdog_api.c
*	author: Moshe Cohen
*	reviewer: Ben Ronen

--------------------------------------------------------------------------------
*******************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define _XOPEN_SOURCE 700

#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

#ifndef NDEBUG
#define DEBUG_ONLY(code) (code)
#else
#define DEBUG_ONLY(code)
#endif

#include <pthread.h> /* pthread_create() */
#include <stdlib.h>  /* setenv(), getenv(), atoi() */
#include <stdio.h>   /* perror(), sprintf() */
#include <assert.h>  /* assert */
#include <unistd.h>  /* fork(), getpid() */
#include <signal.h>  /* sigaction() */
#include <string.h>  /* memset() */
#include <semaphore.h>  /* sem_close() */
#include <sys/types.h>  /* sem_open(), O_CREAT */
#include <sys/stat.h>   /* for mode constants */
#include <fcntl.h>      /* for mode constants */
#include <signal.h>     /* kill() */
#include <sys/wait.h>   /* wait() */

#include "watchdog_api.h"
#include "/home/moshe/git/ds/include/scheduler.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define CHECK_RATE 5

enum boolean_t {FALSE, TRUE};

typedef struct variables
{
    pid_t other_process_pid;
    sched_t *sched;
    sender_t sender;
    time_t send_frequency;
    time_t check_frequency;
    int argc;
    char **argv;
    char *path_name_watchdog;
}vars_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static size_t counter = 0;
static volatile int cleanup_finished = 0;
static pthread_t user_comunicator_thread;
static vars_t vars;

/*~~~~~~~~~~~~~~~~~~~~~~~~static functions signatures~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int Task1Func(void *data); /* I'm alive */
static int Task2Func(void *data); /* counter check. Did I get life signal from the other process? */
static void SignalHandler1(int sig_num);
static void *ManageComunication(void *data);
static void SetEnvs(time_t send_frequency, time_t check_frequency);
static void DefineSigaction(int signum, void(*SaHandlerFunc)(int));
static void WDHandleSigusr2(int sig_num);
static int SemWait(void);
static sem_t *SemOpen(void);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~API functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/********************************* Start **************************************/
int WatchDogStart(sender_t sender, time_t send_frequency, time_t check_frequency,
                                 int argc,char **argv, char *path_name_watchdog)
{
    assert(send_frequency < check_frequency);
    assert(path_name_watchdog);
    assert(argc > 0);

    vars.argv = argv;
    vars.argc = argc;
    vars.sender = sender;
    vars.path_name_watchdog = path_name_watchdog;
    vars.send_frequency = send_frequency;
    vars.check_frequency = check_frequency;

    DefineSigaction(SIGUSR1, SignalHandler1);
    SetEnvs(send_frequency, check_frequency);

    DEBUG_ONLY(printf(BLUE("in WDStart\t")));
    DEBUG_ONLY(printf("in process: |%s|\n",
                          sender == 0? "USER":"WD"));
	if (USER_APP == sender)
	{
		pid_t child_pid = fork();

		if (-1 == child_pid)
		{
			perror("fork");
			return FAILURE;
		}
		else if (0 < child_pid)
		{/* parent(main process) */
			pthread_t thread;
			int status = 0;

            vars.other_process_pid = child_pid;
            if (FAILURE == SemWait())
            {
                return FAILURE;
            }

			status = pthread_create(&thread, NULL,
				 			ManageComunication, NULL);
			if (0 != status)
			{
				fputs("pthread_create FAILED in WDStart\n", stderr);
				return FAILURE;
			}
            user_comunicator_thread = thread;
            pthread_detach(thread);
		}
		else /*if (0 == child_pid)*/
		{/* child process */
            DEBUG_ONLY(printf(GREEN("WD born") "\n"));
			if (-1 == execvp(vars.path_name_watchdog, argv))
			{
				perror("execvp() failed");
				return FAILURE;
			}

		}
	}

	else /* if WD == sender */
	{
        sem_t *sem = SemOpen();
        if (SEM_FAILED == sem)
        {
            return FAILURE;
        }

        vars.other_process_pid = getppid();
        DefineSigaction(SIGUSR2, WDHandleSigusr2);
        sem_post(sem);
        sem_close(sem);
    	ManageComunication(NULL);
	}

	return SUCCESS;
}

/********************************* Stop ***************************************/
void WatchDogStop(void)
{/* sender (always) = USER_APP */
    DEBUG_ONLY(printf(BLUE("in WatchDogStop\n")));
    SchedStop(vars.sched);

    if (SUCCESS != kill(vars.other_process_pid,SIGUSR2))
    {/* failure is rarely. try again:*/
        kill(vars.other_process_pid, SIGUSR2);
    }
    wait(NULL);
    while (1 != cleanup_finished);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~static functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void DefineSigaction(int signum, void(*SaHandlerFunc)(int))
{
    struct sigaction handle;

    memset(&handle, 0, sizeof(handle));
    sigfillset(&handle.sa_mask);
	handle.sa_handler = SaHandlerFunc;
	sigaction(signum, &handle, NULL);
}

/* ~~~~~~~~~~~~~~~ for WDSrart ~~~~~~~~~~~~~~~ */
static void SignalHandler1(int sig_num)
{
    DEBUG_ONLY(printf("%s Catch SIGUSR1\n", vars.sender == 0? "USER":"WD"));
    __sync_add_and_fetch(&counter, 1);
    (void)sig_num;
}

static void *ManageComunication(void *data)
{
	sched_t *sched = NULL;
	ilrd_uid_t uid_task1 = {0};
	ilrd_uid_t uid_task2 = {0};
	ilrd_uid_t bad_uid = UIDGetBadUID();

	sched = SchedCreate();
	if (NULL == sched)
	{
		return NULL;
	}
    vars.sched = sched;
	uid_task1 = SchedAddTask(sched, 1, vars.send_frequency, Task1Func, NULL);
	uid_task2 = SchedAddTask(sched, 2, vars.check_frequency, Task2Func, NULL);
	if (UIDIsSame(uid_task1, bad_uid) || UIDIsSame(uid_task2, bad_uid))
    {
		return NULL;
    }
    DEBUG_ONLY(printf("%s start to send SIGUSR1\n", vars.sender == 0? "USER":"WD"));
    SchedRun(sched);

    SchedDestroy(vars.sched);
    __sync_add_and_fetch(&cleanup_finished, 1);

    (void)data;
    return NULL;
}


static int Task1Func(void *data)
{

    DEBUG_ONLY(printf("send SIGUSR1 from |%d| to |%d| \n",getpid(),
                                          vars.other_process_pid));
	kill(vars.other_process_pid, SIGUSR1);

    (void)data;
	return SUCCESS;
}

static int Task2Func(void *data)
{
    DEBUG_ONLY(printf("process |%d| check signals counter %lu \n",
                                              getpid(), counter));

	if (0 == counter)
    {/* other process died */
		if(USER_APP == vars.sender)
		{/* WD down */
            pid_t child_pid = 0;

            DEBUG_ONLY(printf(RED("The WD is dead") "\n"));
            counter = 0;
            wait(NULL);
            child_pid = fork();
            if (-1 == child_pid)
    		{
    			perror("fork");
    			return FAILURE;
    		}
    		else if (0 < child_pid)
    		{/* parent(thread in user process) */
                vars.other_process_pid = child_pid;
                if (FAILURE == SemWait())
                {
                    return FAILURE;
                }
    		}
    		else
    		{/* child */
                DEBUG_ONLY(printf(GREEN("new WD born") "\n"));
    			if (-1 == execvp(vars.path_name_watchdog, vars.argv))
    			{
    				perror("execvp() failed");
    				return FAILURE;
    			}
    		}
		}
        else /* (WD == sender) */
        {/* user_app down */
            DEBUG_ONLY(printf(RED("The USER_APP is dead") "\n"));
            counter = 0;

            /* Re-Run user_app */
            DEBUG_ONLY(printf(GREEN("new USER_APP born") "\n"));
            if (-1 == execvp(vars.argv[0], vars.argv))
            {
                perror("execvp() failed");
                return FAILURE;
            }
        }
    }
    else /* 0 < counter */
    {/* everything is fine. reset counter */
		counter = __sync_sub_and_fetch(&counter,counter);
    }

    (void)data;

	return SUCCESS;
}

static void SetEnvs(time_t send_frequency, time_t check_frequency)
{
    char freq1[10] = {0};
    char freq2[10] = {0};

    sprintf(freq1,"%ld", send_frequency);
    setenv("SEND_FREQUENCY",freq1, 0);
    sprintf(freq2,"%ld", check_frequency);
    setenv("CHECK_FREQUENCY",freq2, 0);
    /*vars.send_frequency = atoi(freq1);
    vars.check_frequency = atoi(freq2);*/
    setenv("WD_PATH",vars.path_name_watchdog, 0);
}

static int SemWait(void)
{
    sem_t *sem = sem_open("sem", O_CREAT, 0644, 0);
    if (SEM_FAILED == sem)
    {
        sem = sem_open("sem", 0);
        if(sem == NULL)
        {
            perror("sem_open failed");
            return FAILURE;
        }
    }
    sem_wait(sem);
    sem_close(sem);
    sem_unlink("sem");

    return SUCCESS;
}

static sem_t *SemOpen(void)
{
    sem_t *sem = sem_open("sem", O_CREAT, 0644, 0);
    if (SEM_FAILED == sem)
    {
        sem = sem_open("sem", 0);
        if(sem == NULL)
        {
            perror("sem_open failed");
            return SEM_FAILED;
        }
    }

    return sem;
}

/* ~~~~~~~~~~~~~~~ for WDStop ~~~~~~~~~~~~~~~ */

static void WDHandleSigusr2(int sig_num)
{
    DEBUG_ONLY(printf("WD catch SIGUSR2\n"));
    SchedStop(vars.sched);
    /*SchedDestroy(vars.sched);*/
    /*kill(getpid(),SIGTERM);*/
    (void)sig_num;
}
