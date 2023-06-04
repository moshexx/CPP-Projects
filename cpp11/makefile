# make name=stack   ==> default - compile and run with vlg
# make name=stack debug=false vlg=false review=true		==> all possible flags

DIR = $(PWD)
DIRNAME = $(notdir $(DIR))
SRC = $(wildcard $(DIR)/src/*.cpp)
TST = $(wildcard $(DIR)/test/*.cpp)
OBJ = $(addprefix $(DIR)/obj/,$(notdir $(SRC:.cpp=.o)))


CC = g++
CFLAGS = -fpic -pedantic-errors -Wall -Wextra -g #-ansi
INCLUDES = -I $(DIR)/include/ #-lm -lboost_chrono -lboost_thread -lpthread

SRC_FOLDER = src

target = $1
debug = $2
vlg = $3
review = $4

target = $1

ifeq ($(target),)
name = string
else
name = $(target)
endif

ifeq ($(review), true)
	SRC_FOLDER = review
endif

ifeq ($(debug), false)
	CFLAGS = -fpic -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
endif

ifneq ($(vlg), false)
	VAL = valgrind
	VFLAGS = --leak-check=yes --track-origins=yes
endif

all: $(DIR)/obj $(DIR)/bin $(DIR)/lib $(DIR)/bin/$(name)
	$(VAL) $(VFLAGS) $(DIR)/bin/$(name)

$(DIR)/obj:
	mkdir $(DIR)/obj
	
$(DIR)/bin:
	mkdir $(DIR)/bin

$(DIR)/lib:
	mkdir $(DIR)/lib	

$(DIR)/bin/$(name): $(DIR)/test/test_$(name).cpp $(DIR)/lib/lib$(DIRNAME).so 
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES)
	
$(DIR)/lib/lib$(DIRNAME).so: $(OBJ)
	$(CC) $(CFLAGS) -o $@ -shared $^ -lm $(INCLUDES)

$(DIR)/obj/$(name).o: $(DIR)/$(SRC_FOLDER)/$(name).cpp
	$(CC) $(CFLAGS) -c -o $@ -fpic $(DIR)/$(SRC_FOLDER)/$(name).cpp $(INCLUDES)
	
$(DIR)/obj/%.o: $(DIR)/src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ -fpic $^ $(INCLUDES)
	
.PHONY: clean
clean:
	rm -f $(DIR)/bin/* $(DIR)/lib/* $(DIR)/obj/*
	
check:
	$(warning yossi)\
	$(warning moshiko)


