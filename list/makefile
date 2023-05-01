# command line:
# make debug 	- compile debug mode 
# make release 	- compile release mode
# make clean 	- clean the bin files 

CC = g++

# define any compile-time flags
CFLAGS = -pedantic-errors -Wall -Wextra -g

# define any compile-time flags
CFLAGS_RELEASE = -pedantic-errors -Wall -Wextra -DNDEBUG -O3

# define any directories containing header files
INCLUDES = -I include -lpthread

# define the C++ file
FILE = test_list
FILE_NAME = $(FILE).cpp


.PHONY: test

all:

debug:
	$(CC) $(CFLAGS) $(FILE_NAME) $(INCLUDES) -o bin/$(FILE)_debug.out
	
release:
	$(CC) $(CFLAGS_RELEASE) $(FILE_NAME) $(INCLUDES) -o bin/$(FILE)_release.out

clean:
	$(RM) $(wildcard bin/*.out)	
# DO NOT DELETE THIS LINE -- make depend needs it
