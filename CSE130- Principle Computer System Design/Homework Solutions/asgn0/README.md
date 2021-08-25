# Assignment 0 README for CSE 130, Fall 2019
Derrick DeBose

This repo contains the files needed to compile and run the dog program for Assignment 0

# Files

* `README.md`: This is a markdown file that will explain what each file does
* `DESIGN.pdf`: This is a pdf file that will explain the logic behind my code according to the required standards.
* `Makefile`: This is a `Makefile` that I will use to build Assignment 0.
* `WRITEUP.pdf`: This is a pdf file that will explain the difference between reading a file and reading from standard input.
* `dog.cpp`: This is a C++ file that will do the same thing as the cat command in the terminal.

There is a problem with the dog.cpp file. I have an error whenever the "-" command is used. On lines 45-58, after reading from the standard input, the code will print "Bad Address" before printing out the output. Then when the next STDIN lines are read in, the code will stop printing "Bad Address" and only print the correct output. If I remove the warning call, the operation stops working properly altogether. According to https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html, "'Bad address.' An invalid pointer was detected. On GNU/Hurd systems, this error never happens; you get a signal instead." I am unsure what my invalid pointer is on the first STDIN but does not occur afterwards and I am unsure of how I get a signal and not an error. The ./dog command works just fine but the ./dog - command prints the error.