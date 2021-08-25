/*Derrick DeBose*/
/*Assignment 3*/
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

#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

#include <signal.h>
#include <list>  

#define LISTEN_BL 100
#define PORT 80
#define CACHE_SIZE 2

void pack_contents(struct cache_arguments* arguments);
bool in_cache(struct cache_arguments *arguments);
void get(struct cache_arguments *parameters);
void put(struct cache_arguments *parameters);
int64_t getFileSize(struct cache_arguments *parameters);
bool invalid_name(char filename[]);
void FreeCache(int sig);

struct cache_arguments{
	char* filename;
	char* command;
	char* http;
	char *content;
	int sock_id;
	uint64_t content_length;
};

std::list <cache_arguments> cache;
char* logFile;
int cflag = 0;
int log = false;
//Some of this code comes from the section slides about setting up the server.
int main(int argc, char *argv[]){ 
	int server_fd, new_socket;
	struct sockaddr_in address; 
	int addrlen = sizeof(address); 
	int opt;
	//bad start up of server if no command line arguments
	if(argc == 1){
		perror("Not enough Arguments");
		exit(EXIT_FAILURE); 
	}
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	//IPv4 addresses
	address.sin_family = AF_INET; 

	while((opt = getopt(argc, argv, "c l:")) != -1){
		printf("this is opt: %c\n", opt);
		switch(opt){
			case 'c':
				cflag = 1;
				continue;
			case 'l':
				log = 1;
				continue;
			default:
				continue;
		}
	}

	if(cflag && log){
		for(int i = 1; i < argc; ++i) {
			if(strcmp("-l", argv[i]) == 0){
				logFile= argv[i+1];
				int fd2 = open(logFile, O_CREAT | O_TRUNC, S_IRWXU);
				close(fd2);
			}
		}
		if (strcmp(argv[4],"localhost") == 0){
		//will connect to default IP address
			printf("found local host: %s\n", argv[4]);
			address.sin_addr.s_addr = INADDR_ANY;
		}else{
			printf("local host not found %s\n", argv[4]);
			address.sin_addr.s_addr = inet_addr(argv[4]);
		}
		if(argc == 6){
			address.sin_port = htons( atoi(argv[5]) );
			printf("found port number:%d \n", atoi(argv[5]));
		}
		else{
			printf("default port number \n");
			address.sin_port = htons( PORT );
		}
	}
	else if(cflag){
		if (strcmp(argv[2],"localhost") == 0){
		//will connect to default IP address
			printf("found local host: \n");
			address.sin_addr.s_addr = INADDR_ANY;
		}else{
			printf("local host not found \n");
			address.sin_addr.s_addr = inet_addr(argv[2]); 
		}
		if(argc == 4){
			address.sin_port = htons( atoi(argv[3]) );
			printf("found port number:%d \n", atoi(argv[3]));
		}
		else{
			printf("default port number \n");
			address.sin_port = htons( PORT );
		}
	}
	else if(log){
		for(int i = 1; i < argc; ++i) {
			if(strcmp("-l", argv[i]) == 0){
				logFile= argv[i+1];
				int fd2 = open(logFile, O_CREAT | O_TRUNC, S_IRWXU);
				printf("This is the logFile: %s and fd2: %d\n",logFile, fd2 ); 
				close(fd2);
			}
		}
		if (strcmp(argv[3],"localhost") == 0){
		//will connect to default IP address
			printf("found local host: \n");
			address.sin_addr.s_addr = INADDR_ANY;
		}else{
			printf("local host not found \n");
			address.sin_addr.s_addr = inet_addr(argv[3]); 
		}
		if(argc == 5){
			address.sin_port = htons( atoi(argv[4]) );
			printf("found port number:%d \n", atoi(argv[4]));
		}
		else{
			printf("default port number \n");
			address.sin_port = htons( PORT );
		}
	}
	else{// no flags
		if (strcmp(argv[1],"localhost") == 0){
		//will connect to default IP address
			printf("found local host: \n");
			address.sin_addr.s_addr = INADDR_ANY;
		}else{
			printf("local host not found \n");
			address.sin_addr.s_addr = inet_addr(argv[1]); 
		}
		if(argc == 3){
			printf("found port number:%d \n", atoi(argv[2]));
			address.sin_port = htons( atoi(argv[2]) );
		}
		else{
			printf("default port number \n");
			address.sin_port = htons( PORT );
		}
		printf("this is no flags");
	}

	// Attaching socket to the port 
	if (bind(server_fd, (struct sockaddr *)&address,  
								 sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, LISTEN_BL) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	//while loop to accept multiple 
	while(1){
		printf("Top of loop\r\n"); 
		signal(SIGINT, FreeCache);
		//accept the client connection 
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		}
		ssize_t readCount; 
		char buffer[1024] = {0};
		char hexbuf[1024] = {0};
		int64_t num = 0;
		struct cache_arguments *arguments;
		arguments = new cache_arguments;
		arguments->sock_id = new_socket;
		// read the client request
		readCount = read(new_socket , buffer, sizeof(buffer));
		printf("This is the buffer: %s\n",buffer ); 
		//command is a get or put request
		//filename is the name of the file read in from the client
		//http is used for the reponse
		char* command = new char[50];
		char* filename = new char[50];
		char* http = new char[50];

		uint64_t *content_length = new uint64_t(0);
		char* nl_split = NULL;
		//split the get and put requests on the new line character.
		nl_split = strtok(buffer, "\r\n");
		// Im going to check the first token to find
		// the request and the filename requested.
		// do an sscanf for figuring out command line arguments
		sscanf(nl_split, "%s %s %s", command, filename, http);
		while (nl_split != NULL)
		{
			//Loop to find content length
			int scan1 = sscanf(nl_split, "Content-Length:%ld", content_length);
			printf("This is the scan1: %i\n",scan1 ); 
			nl_split = strtok(NULL, "\r\n");
		}
		arguments->filename = filename;
		arguments->command = command;
		arguments->http = http;
		arguments->content_length = *content_length;
		printf("This is the content_length: %ld\n",arguments->content_length );  

		//Status 500
		if(!(strcmp(command,"GET")==0 || strcmp(command,"PUT")==0)){
			if(log){
				num = sprintf(hexbuf, "FAIL: %s %s HTTP/1.1 --- response 500\n========\n", command, filename);
				int fd2 = open(logFile, O_WRONLY, S_IRWXU);
				write(fd2, hexbuf, num);
				close(fd2);
				dprintf(new_socket, "%s 500 Internal Server Error\r\n", http);
			}
			else{
				dprintf(new_socket, "%s 500 Internal Server Error\r\n", http);
			}
			close(new_socket);
			delete(arguments);
			continue;
		}
		//Status 400
		else if(invalid_name(filename)){
			if(log){
				num = sprintf(hexbuf, "FAIL: %s %s %s --- response 400\n========\n", command, filename, http);
				int fd2 = open(logFile, O_WRONLY, S_IRWXU);
				write(fd2, hexbuf, num);
				close(fd2);
				dprintf(new_socket, "%s 400 Bad Request\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", arguments->content_length);
			}
			else{
				dprintf(new_socket, "%s 400 Bad Request\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", arguments->content_length);
			}
			close(new_socket);
			delete(arguments);
			continue;
		}
		if(cflag){
			printf("In queue1:\n");
			std::list<cache_arguments>::iterator iter;
			for( iter = cache.begin(); iter != cache.end(); ++iter){
				printf("%s\n", iter->filename);

			}
			printf("out queue1:\n");

			if(in_cache(arguments)){
				printf("if in_cache\n");
				if(strcmp(arguments->command, "GET")==0){
					//GET Requests
					get(&cache.front());
				}
				else{// must be a put request
					cache.pop_front();
					pack_contents(arguments); 
					cache.push_front(*arguments);
				}
			}
			// cache == max size and a put
			else if(cache.size() == CACHE_SIZE && strcmp(arguments->command, "PUT")==0){
				pack_contents(arguments);
				cache.push_front(*arguments);
				struct cache_arguments *params = &cache.back();
				put(params);
				// pop back automatically deleted allocated memory
				cache.pop_back();
			}
			// cache != max size and a put
			else if(cache.size() < CACHE_SIZE && strcmp(arguments->command, "PUT")==0){
				//cache not full so push put struct
				pack_contents(arguments);
				cache.push_front(*arguments);
			}
			//must be GET Requests thats not in cache
			else{ 
				arguments->content_length = getFileSize(arguments);
				printf("getfilesize: This is the content_length: %ld\n",arguments->content_length );
				if(arguments->content_length != 0){
					get(arguments);
				}
			}
			printf("In queue2:\n");

			for( iter = cache.begin(); iter != cache.end(); ++iter){
				printf("%s\n", iter->filename);

			}
			printf("out queue2:\n");

		}
		else{//do a put or get requests
			if (strcmp(command,"GET")==0){
				arguments->content_length = getFileSize(arguments);
				if(!(arguments->content_length == 0)){
					get(arguments);
				}
			}
			//PUT Requests
			else if(strcmp(command,"PUT") ==0){
				put(arguments);
			}
			delete(arguments);
		}
		printf("bottom of loop\n");

		close(new_socket);
		
	}
	return 0; 
	close(server_fd);
} 

//clear cache before closing server
void FreeCache(int sig){
	signal(sig, SIG_IGN);
	while(cache.size() != 0){
		printf("this cache.size(): %zu\n", cache.size());
		std::list<cache_arguments>::iterator iter;
		for( iter = cache.begin(); iter != cache.end(); ++iter){
			printf("%s\n", iter->filename);
		}
		struct cache_arguments *params = &cache.back();
		put(params);
		cache.pop_back();
		for( iter = cache.begin(); iter != cache.end(); ++iter){
			printf("%s\n", iter->filename);
		}
	}
	exit(0);
}

//used to pack the contents of put request into cache
void pack_contents(struct cache_arguments* arguments){
	char* filename = arguments->filename;
	uint64_t content_length = arguments->content_length;
	char* http = arguments->http;
	ssize_t read_count = 1;
	int64_t num = 0;
	ssize_t number = 0;
	int fd = 0;
	char hexbuf[1024] = {0}; 
	int status =0;
	if ((fd=open(filename, O_TRUNC , S_IRWXU)) == -1){
		status = 201;
	}
	else{
		status = 200; 
	} 
	close(fd);
	if(content_length > 0){
		char* content = new char[content_length];
		arguments->content = content;
	}
	while (content_length >0 && read_count > 0){
		unsigned char buf[50] = {0}; 
		read_count = read(arguments->sock_id, buf, sizeof(buf));
		strcat(arguments->content, (char*)buf);
		content_length -= read_count;


	}
	//logging the put request
	if(in_cache(arguments)){
		num = sprintf(hexbuf, "%s %s length %li [was in cache]\n", arguments->command, arguments->filename,  arguments->content_length);

	}else{
		num = sprintf(hexbuf, "%s %s length %li [was not in cache]\n", arguments->command, arguments->filename,  arguments->content_length);
	}
	int fd2 = open(logFile, O_WRONLY | O_APPEND, S_IRWXU);
	number = write(fd2, hexbuf, num);
	uint64_t counter = 0;
	content_length = arguments->content_length;
	uint64_t log_count = 0;
	while(content_length > 0 && counter <= arguments->content_length){
		unsigned char buf[20] = {0}; 
		read_count = 20;
		for(int i=0;i<20;++i){
			if(counter==arguments->content_length){
				read_count = i;
			}
			if(counter <= arguments->content_length){
				buf[i] = arguments->content[counter++];
			}
		}
		num = sprintf(hexbuf, "%08lu ", log_count);
		number = write(fd2, hexbuf, num);
		for(ssize_t i =0; i < read_count; ++i ){
			num = sprintf(hexbuf, "%02x ", buf[i]);
			number = write(fd2, hexbuf, num);
		}
		num = sprintf(hexbuf, "\n");
		number = write(fd2, hexbuf, num);
		content_length -= read_count;
		log_count +=20;
	}
	num = sprintf(hexbuf, "========\n");
	number = write(fd2, hexbuf, num);
	close(fd2);
	if(status== 201){
		dprintf(arguments->sock_id, "%s %i Created\r\n" , http, status);
	}else{
		dprintf(arguments->sock_id, "%s %i OK\r\n" , http, status);
	}
		dprintf(arguments->sock_id, "Content-Length:0\r\n\r\n");
	return;
}

// This is a method to check to see if the filename is in the cache or not
// If the filename is in the cache then it will also be moved to the front 
// to maintain LRU order
bool in_cache(struct cache_arguments* arguments){
	std::list<cache_arguments>::iterator iter;
	for(iter = cache.begin(); iter != cache.end(); ++iter){
		if(strcmp(arguments->filename, iter->filename)==0){
			arguments->filename = iter->filename;
			arguments->http = iter->http;
			arguments->sock_id = iter->sock_id;
			if(strcmp(arguments->command, "GET") == 0){
				arguments->content_length = iter->content_length;
				arguments->content = iter->content;
			}
			cache.push_front(*arguments);
			cache.erase(iter);
			return true;
		}

	}
	return false;
}

void get(struct cache_arguments *parameters){
	struct cache_arguments *arguments = parameters;
	char* filename = arguments->filename;
	int new_socket = arguments->sock_id;
	uint64_t content_length = arguments->content_length;
	uint64_t content = arguments->content_length;
	int64_t num = 0;
	char* http = arguments->http;
	char hexbuf[1024] = {0}; 
	ssize_t  read_count = 1, sent = 1;
	//second buffer to be able to read and write files
	char buf[32] = {0}; 
	bool cached = false;
	printf("GET1: This is the arguments->content_length: %lu\n",arguments->content_length );
	if(log && cflag){
		if (in_cache(parameters)){
			cached = true;
			num = sprintf(hexbuf, "GET %s length 0 [was in cache]\n========\n", filename);
		}
		else{
			num = sprintf(hexbuf, "GET %s length 0 [was not in cache]\n========\n", filename);
		}
		printf("this is num: %ld\n", num);
		int fd2 = open(logFile, O_WRONLY | O_APPEND, S_IRWXU);
		write(fd2, hexbuf, num);
		close(fd2);
		printf("Printing get ok message\n");
		dprintf(new_socket, "%s 200 OK\r\n", http);
		dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content);
	}
	else if(cflag){
		if (in_cache(parameters)){
			cached = true;
		}
		dprintf(new_socket, "%s 200 OK\r\n", http);
		dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content);
	}
	else if(log){
		num = sprintf(hexbuf, "GET %s length 0\n========\n", filename);
		int fd2 = open(logFile, O_WRONLY | O_APPEND, S_IRWXU);
		write(fd2, hexbuf, num);
		close(fd2);
		dprintf(new_socket, "%s 200 OK\r\n", http);
		dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content);
	}
	else{
		dprintf(new_socket, "%s 200 OK\r\n", http);
		dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content);

	}
	int fd = 0;
	if(!cached){
		fd = open(filename, O_RDONLY, S_IRWXU);
	}
	while(content_length > 0){
		if (cached){
			send(new_socket , arguments->content, arguments->content_length , 0 );
			content_length -= arguments->content_length;
		}
		else{
			read_count = read(fd, buf, sizeof(buf));
			sent = send(new_socket , buf, read_count , 0 ); 
			content_length -= sent;
		}
	}
	if(!cached){
		close(fd);
	}
	printf("End of get\n");
}

void put(struct cache_arguments *parameters){
	struct cache_arguments *arguments = parameters;
	char* filename = arguments->filename;
	int new_socket = arguments->sock_id;
	uint64_t content_length = arguments->content_length;
	char* http = arguments->http;
	char* command = arguments->command;
	int64_t num = 0;
	ssize_t number = 0;
	int fd = 0;
	ssize_t read_count = 1, write_count = 1;
	unsigned char buf[20] = {0};
	char hexbuf[1024] = {0}; 
	int status =0;
	if ((fd=open(filename, O_TRUNC , S_IRWXU)) == -1){
		status = 201;
	}
	else{
		status = 200; 
	} 
	close(fd);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

	if (fd < 0){
		printf(" Value of errno: %d\n ", errno); 
		printf("The error message is : %s\n",  strerror(errno)); 
		if (errno == EACCES){
			if (log && cflag){
				num = sprintf(hexbuf, "FAIL: %s %s %s --- response 403 [was not in cache]\n========\n", command, filename, http);
				//log_offset = global_log_offset;
				//global_log_offset +=num;
				printf("this is num: %ld\n", num);
				//printf("PUT: this is arguments->log_offset: %lu\n", log_offset);
				//printf("this is global_log_offset: %lu\n", global_log_offset);
				int fd2 = open(logFile, O_WRONLY | O_APPEND, S_IRWXU);
				write(fd2, hexbuf, num);
				//log_offset+=num;
				close(fd2);
				dprintf(new_socket, "%s 403 Forbidden\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
			}
			else if (log){
				num = sprintf(hexbuf, "FAIL: %s %s %s --- response 403\n========\n", command, filename, http);
				//log_offset = global_log_offset;
				//global_log_offset +=num;
				printf("this is num: %ld\n", num);
				//printf("PUT: this is arguments->log_offset: %lu\n", log_offset);
				//printf("this is global_log_offset: %lu\n", global_log_offset);
				int fd2 = open(logFile, O_WRONLY | O_APPEND, S_IRWXU);
				write(fd2, hexbuf, num);
				//log_offset+=num;
				close(fd2);
				dprintf(new_socket, "%s 403 Forbidden\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
			}
			else{
				dprintf(new_socket, "%s 403 Forbidden\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
			}
		}
		close(fd);
		return;
	}
	if (log && cflag){//must be in cache
		write_count = write(fd, arguments->content, arguments->content_length);
		close(fd);
	}
	else if(cflag){
		write_count = write(fd, arguments->content, arguments->content_length);
		close(fd);
	}
	else if(log){
		num = sprintf(hexbuf, "%s %s length %li\n", command, filename, content_length);
		int fd2 = open(logFile, O_WRONLY | O_APPEND, S_IRWXU);
		number = write(fd2, hexbuf, num);
		uint64_t counter = 0;
		uint64_t content = content_length;
		while(content_length >0 && read_count > 0 && counter < content){
			read_count = recv(new_socket , buf, sizeof(buf), 0); 
			num = sprintf(hexbuf, "%08lu ", counter);
			number = write(fd2, hexbuf, num);
			for(ssize_t i =0; i < read_count; ++i ){
				num = sprintf(hexbuf, "%02x ", buf[i]);
				number = write(fd2, hexbuf, num);
			}
			num = sprintf(hexbuf, "\n");
			number = write(fd2, hexbuf, num);
			write_count = write(fd, buf, read_count);
			counter+=20;
			content_length -= write_count;
		}
		num = sprintf(hexbuf, "========\n");
		number = write(fd2, hexbuf, num);
		close(fd2);
		close(fd);
		if(status== 201){
			dprintf(new_socket, "%s %i Created\r\n" , http, status);
		}else{
			dprintf(new_socket, "%s %i OK\r\n" , http, status);
		}
		dprintf(new_socket, "Content-Length:0\r\n\r\n");
	}
	else{
		while(content_length >0){
			read_count = recv(new_socket , buf, sizeof(buf), 0); 
			write_count = write(fd, buf, read_count);
			content_length -= write_count;
		}
		close(fd);
		if(status== 201){
			dprintf(new_socket, "%s %i Created\r\n" , http, status);
		}else{
			dprintf(new_socket, "%s %i OK\r\n" , http, status);
		}
		dprintf(new_socket, "Content-Length:0\r\n\r\n");
	}
	printf("end of put\n");
}

// gets the filesize from get if not in the cache
int64_t getFileSize(struct cache_arguments *parameters){
	struct cache_arguments* arguments = parameters;
	char* filename = arguments->filename;
	int new_socket = arguments->sock_id;
	char* http = arguments->http;
	char hexbuf[1024] = {0};
	int64_t num = 0;
	uint64_t content_length = 0;
	int fd = open(filename, O_RDONLY, S_IRWXU);
	if (fd < 0){
		printf(" Value of errno: %d\n ", errno); 
		printf("The error message is : %s\n",  strerror(errno)); 
		if(errno == 2){
			if (log){
				num  = sprintf(hexbuf, "FAIL: GET %s %s --- response 404 [was not in cache]\n========\n", filename, http);
				printf("this is num: %ld\n", num);
				int fd2 = open(logFile, O_WRONLY | O_APPEND, S_IRWXU);
				write(fd2, hexbuf, num);
				close(fd2);
				dprintf(new_socket, "%s 404 File Not Found\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
			}
			else{
				dprintf(new_socket, "%s 404 File Not Found\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);

			}
		}else if (errno == EACCES){
			if (log){
				num = sprintf(hexbuf, "FAIL: GET %s %s --- response 403 [was not in cache]\n========\n", filename, http);
				printf("this is num: %ld\n", num);
				int fd2 = open(logFile, O_WRONLY | O_APPEND, S_IRWXU);
				write(fd2, hexbuf, num);
				close(fd2);
				dprintf(new_socket, "%s 403 Forbidden\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
			}
			else{
				dprintf(new_socket, "%s 403 Forbidden\r\n", http);
				dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
			}
		}
		close(fd);
		return 0;
	}
	ssize_t read_count = 1;
	char buf[32] = {0}; 
	while(read_count > 0){
		read_count = read(fd, buf, sizeof(buf));
		if (read_count > 0){
			content_length += read_count;
		}
	}
	close(fd);
	return content_length;
}

// make sure the file name is valid or not
bool invalid_name(char filename[]){
	if(strlen(filename) != 27){
		return true;
	}
	else{
		//we know that the code will be exactly 27 chanacters
		for(int i = 0; i != 27; ++i){
			//check every character to see if filename has only
			//valid character
			if( (filename[i]>='a' && filename[i]<='z') || 
				(filename[i]>='A' && filename[i]<='Z') || 
				(filename[i]>='0' && filename[i]<='9') || 
				filename[i] == '-' || filename[i] == '_'){
				//if valid char continue
				continue;
			}
			else{
				//invalid name
				return true;
			}

		}
		//must be a valid name
		return false;
	}

}

