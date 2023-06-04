# command line:
# make vlg 		- compile debug mode, run with valgrind
# make debug 	- compile debug mode & run 
# make release 	- compile release mode & run 
# make clean 	- clean the files (recommended to run between different compilation)

CC = g++

# define any compile-time flags
CFLAGS = -pedantic-errors -Wall -Wextra -g

# define any compile-time flags
CFLAGS_RELEASE = -pedantic-errors -Wall -Wextra -DNDEBUG -O3

# define any directories containing header files
INCLUDES = -I include -lpthread

VLG = valgrind --leak-check=yes --track-origins=yes

# define the C++ file
FILE = test_list
FILE_NAME = $(FILE).cpp


.PHONY: test

all:

debug:
	$(CC) $(CFLAGS) $(FILE_NAME) $(INCLUDES) -o bin/$(FILE)_debug.out
	bin/$(FILE)_debug.out 

vlg:
	$(CC) $(CFLAGS) $(FILE_NAME) $(INCLUDES) -o bin/$(FILE)_debug.out
	$(VLG) bin/$(FILE)_debug.out 
	
release:
	$(CC) $(CFLAGS_RELEASE) $(FILE_NAME) $(INCLUDES) -o bin/$(FILE)_release.out
	bin/$(FILE)_release.out 

clean:
	$(RM) $(wildcard bin/*.out)	
# DO NOT DELETE THIS LINE -- make depend needs it
