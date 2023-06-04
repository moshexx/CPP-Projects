# the compiler: 
CCPP = g++
CC = gcc

# compiler flags:
#  -Wall turns on most, but not all, compiler warnings
#  -Wextra enables some of Wall's questionable warnings
#  -ansi C89 c standart
#  -pedantic-errors Whenever the base standart requires diagnostics (undefined in compile)
CPPFLAGS = #-std=c++98 -pedantic-errors -Wall -Wextra
CFLAGS = #-ansi -pedantic-errors -Wall -Wextra


#  -g adds debugging information
DEBUG_FLAGS_CPP = $(CCPP) $(CPPFLAGS) -g
DEBUG_FLAGS_C = $(CC) $(CFLAGS) -g
#  -O3 optimization degree
#  -DNDEBUG do not debug
RELEASE_FLAGS_C = $(CC) $(CFLAGS) -DNDEBUG -O3
RELEASE_FLAGS_CPP = $(CCPP) $(CPPFLAGS) -DNDEBUG -O3

FLAGSC = 
FLAGSCPP = 
KIND = 
MODE = $2

all: test 
ifeq ($(MODE),r)
FLAGSC = $(RELEASE_FLAGS_C)
FLAGSCPP = $(RELEASE_FLAGS_CPP)
KIND = _release
else
FLAGSC = $(DEBUG_FLAGS_C)
FLAGSCPP = $(DEBUG_FLAGS_CPP)
KIND=_debuge
endif

.PHONY: test clean

test: cfile cppfile
	meld cfile.txt cppfile.txt

cfile: cfile_preper
	./cpp2c_c.out > cfile.txt
	
cppfile: cppfile_preper
	./cpp2c.out > cppfile.txt

cfile_preper: cpp2c_c.c
	$(FLAGSC) cpp2c_c.c -o cpp2c_c.out

cppfile_preper: cpp2c.cpp
	$(FLAGSCPP) cpp2c.cpp -o cpp2c.out
	


clean:
	rm -f ./*.out ./*.txt 

