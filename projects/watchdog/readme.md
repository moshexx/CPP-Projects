README file for watchdog:
-------------------------

1.What is watchdog(aka WD) application?
WD is a program that runs simultaneously to another program (any user program you
will choose).
WD guaranteed to start the user program again, in case the program will fail
(for any reason).

2.How is the watchdog application "watch" the user program?
WD program will start a new process that will communicate with the user process.
User process will be "watched" from calling function StartWD(), till StopWD().

3.What happens if WD program failed
In that case, WD will start again automatically as long user program doesn't
fail in the meantime.

4."watch" frequency:
The user can set different frequencies to watch the user and the WD.
Lower frequency will affect the program safety (it will take a longer time to
recover).
High frequency will affect performance

frequencies limits - measure in seconds:
frequency should be at least 3 sec and no more than 99999999
recommend frequency while running memcheck tool(Valgrind): minimum freq 7

 5.How to install the debug version?
  run from linux command line (from watchdog package directory):
  $ make clean
  $ make debug FILE=user_app

  installation:
  -------------------------
 1.How to install the release version?
  run from linux command line (from watchdog package directory):
  $ make clean
  $ make release FILE=user_app

2.How to install the debug version and run with Valgrind?
  run from linux command line (from watchdog package directory):
  $ make clean
  $ make vlg FILE=user_app

3.How to change the program user wants to run with WD?
  Replace the program in the files directory named: user_app.c
  install again (step 1 / 2 / 3)

4.How to run user program with WD after install?
  user_app.out and watchdog.out executable are at /watchdog/bin
  run from linux command line:
  $ (add path)/watchdog/bin/user_app.out (add path)/watchdog/bin/watchdog.out
