#------------------------------------------------------------------------------------------------
# Derrick DeBose
# Makefile
# Automates creation of executable binary file
# Role in Project: speed up compiling and testing, needed for checker and for grading purposes
# -----------------------------------------------------------------------------------------------s

FLAGS   = -std=c99 -Wall
SOURCES = apint.c apint.h PA2.c
OBJECTS = apint.o PA2.o
EXEBIN  = PA2

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)


