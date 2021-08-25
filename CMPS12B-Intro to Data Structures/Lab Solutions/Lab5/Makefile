#------------------------------------------------------------------------------------------------
# Derrick DeBose
# Makefile
# Automates creation of executable binary file
# Role in Project: speed up compiling and testing, needed for checker and for grading purposes
# -----------------------------------------------------------------------------------------------s

FLAGS   = -std=c99 -Wall
SOURCES = queue.c queue.h queueClient.c
OBJECTS = queue.o queueClient.o
EXEBIN  = queueClient

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)


