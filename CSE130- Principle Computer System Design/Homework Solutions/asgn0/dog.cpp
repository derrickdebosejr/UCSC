/*Derrick DeBose*/
/*Assignment 0*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>
#include <cstddef>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, const char *argv[]){
	uint16_t counter = 1; 
	char* buffer [32];
	//readCount and writeCount are the returned values from
	//the read() and write() functions.
	ssize_t readCount =1;
	ssize_t writeCount =1;
	//accounts for the case of no arguments and reading STDIN
	if (counter == argc){
		//readCount and writeCount return 0 when there is an EOF
		while(readCount!=0 || writeCount!= 0){
			readCount = read(STDIN_FILENO, *buffer, 1);
			//detect read errors
			if (readCount < 0){
				perror(argv[counter]);
			}

			writeCount = write(STDOUT_FILENO, *buffer, readCount);
			//detect write errors
			if (writeCount < 0){
				perror(argv[counter]);
			}
		}
	}
	while (counter < argc){
		//allows us to use the same name even if error occured before
		readCount =1;
		writeCount =1;
		if (strcmp(argv[counter],"-")==0){
			//readCount and writeCount return 0 when there is an EOF
			while(readCount!=0 || writeCount!= 0){
				readCount = read(STDIN_FILENO, *buffer, 1);
				//used to detected read() errors
				//This creates the Bad Address error
				//I am unsure of how to fix this error.
				if (readCount < 0){
					perror(STDIN_FILENO);
				}
				writeCount = write(STDOUT_FILENO, *buffer, readCount);
				//used to detected write() errors
				if (writeCount < 0){
					perror(STDIN_FILENO);
				}
			}
			++counter;
			continue;
		}
		//this is to ensure we do not try to open the file " - "
		else{
			int file = open(argv[counter], O_RDONLY);
			//file was not successfully opened
			if (file < 0){
				perror(argv[counter]);
				close(file);
				++counter;
				continue;
			}
			//readCount and writeCount return 0 when there is an EOF
			while(readCount!=0 || writeCount!= 0){
				readCount = read(file, *buffer, 1);
				//ensure we are not reading a folder
				if (readCount < 0){
					perror(argv[counter]);
					close(file);
					++counter;
					continue;
				}
				writeCount = write(STDOUT_FILENO, *buffer, readCount);
				//used to detected write() errors
				if (writeCount < 0){//no file
					perror(argv[counter]);
					close(file);
					++counter;
					continue;
				}

			}
			close(file);
		}
		
		
		++counter;
	}
}
