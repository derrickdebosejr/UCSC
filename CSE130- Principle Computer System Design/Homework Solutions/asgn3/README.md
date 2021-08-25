# Assignment 3 README for CSE 130, Fall 2019
Derrick DeBose

This repo contains the files needed to compile and run the httpserver program for Assignment 3

# Files

* `README.md`: This is a markdown file that will explain what each file does
* `DESIGN.pdf`: This is a pdf file that will explain the logic behind my code according to the required standards.
* `Makefile`: This is a `Makefile` that I will use to build Assignment 3.
* `WRITEUP.pdf`: This is a pdf file that will explain the what happens if ending communication early for a put request happens.
* `httpserver.cpp`: This is a C++ file that will create a caching server that will let a client do get and put requests on the server.

Used the starter code that was given in dicussion section, the same information can be found on: https://www.geeksforgeeks.org/socket-programming-cc/ 
When starting up the server I am testing that only good arguments are going to be use.
For example:
./httpserver is invalid

Valid arguments:
We have to use sudo when starting up the server to gain permissions to set the default port 80. When using sudo, the forbidden status code can not occur because sudo gives permissions of all files on the server.
sudo ./httpserver localhost
sudo ./httpserver 127.0.0.10

When using large port numbers on the server, we do not need to use sudo because special permissions are not required to use port over 1024.
./httpserver localhost 8000
./httpserver 127.0.0.10 8000

You can use the flag -c to signal that you want to cache
You can use the flag -l logFile to choose to write to that logFile 

Assume: The port number must follow the hostname, for example:

./httpserver -l logFile 127.0.0.10 -c 8000 
