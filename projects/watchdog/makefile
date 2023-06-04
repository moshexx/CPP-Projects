# compile:
# make vlg FILE=user_app
# make debug FILE=user_app
# make release FILE=user_app

CC = gcc

# define any compile-time flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

# define any compile-time flags
CFLAGS_RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

# define any directories containing header files other than /usr/include
INCLUDES = -I include 

LIBS = -Wl,-rpath=lib/ lib/debug.so
LIBS_RELEASE = -Wl,-rpath=lib/ lib/release.so 
VLG = valgrind --leak-check=yes --track-origins=yes


# define the C source files
FILE =
FILE_NAME = $(FILE).c


.PHONY: test

all:

debug:
	$(CC) $(CFLAGS) src/watchdog.c src/watchdog_api.c $(INCLUDES) $(LIBS) -lpthread -lm -o bin/wd.out
	$(CC) $(CFLAGS) user_files/$(FILE_NAME) src/watchdog_api.c $(INCLUDES) $(LIBS) -lpthread -lm -o bin/$(FILE).out
	bin/$(FILE).out 

vlg:
	$(CC) $(CFLAGS) src/watchdog.c src/watchdog_api.c $(INCLUDES) $(LIBS) -lpthread -lm -o bin/wd.out
	$(CC) $(CFLAGS) user_files/$(FILE_NAME) src/watchdog_api.c $(INCLUDES) $(LIBS) -lpthread -lm -o bin/$(FILE).out
	$(VLG) bin/$(FILE).out 
	
release:
	$(CC) $(CFLAGS_RELEASE) src/watchdog.c src/watchdog_api.c $(INCLUDES) $(LIBS_RELEASE) -lpthread -lm -o bin/wd.out		
	$(CC) $(CFLAGS_RELEASE) user_files/$(FILE_NAME) src/watchdog_api.c $(INCLUDES) $(LIBS_RELEASE) -lpthread -lm -o bin/$(FILE).out
	bin/$(FILE).out 

clean:
	$(RM) $(wildcard bin/*.out)	
# DO NOT DELETE THIS LINE -- make depend needs it
