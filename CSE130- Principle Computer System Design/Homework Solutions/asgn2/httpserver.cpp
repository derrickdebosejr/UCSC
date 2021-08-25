/*Derrick DeBose*/
/*Assignment 2*/
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

#include <pthread.h>
#include <queue> 

#define LISTEN_BL 100
#define PORT 80

int queue_socket_id();
void process_requests(void* parameters);
void *client_reqs(void* parameters);
void get(void* parameters);
void put(void* parameters);
int64_t getFileSize(void* parameters);
bool invalid_name(char filename[]);

struct thread_arguments{
	char* filename;
	char* command;
	char* http;
	int sock_id;
	int64_t content_length;
	bool log;
	char* logFile;
	uint64_t log_offset;
};
pthread_mutex_t lock;
pthread_cond_t conditional;
uint64_t global_log_offset = 0;
std::queue <int> requests;
//Some of this code comes from the section slides about setting up the server.
int main(int argc, char *argv[]){ 
	int server_fd, new_socket;
	struct sockaddr_in address; 
	int addrlen = sizeof(address); 
	char* logFile;
	int opt;
	int nflag = 0;
	size_t N = 4;
	bool log = false;
	//do an sscanf for figuring out command line arguments
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
	printf("This is before getopt\n");
	for(int i = 0; i < argc; ++i) {
		printf ("%s ", argv[i]);
	}
	printf("\n");
	while((opt = getopt(argc, argv, "N: l:")) != -1){
		printf("this is opt: %c\n", opt);
		switch(opt){
			case 'N':
				nflag = 1;
				continue;
			case 'l':
				log = true;
				continue;
			default:
				continue;
		}
	}
	printf("This is after getopt\n");
	for(int i = 0; i < argc; ++i) {
		printf ("%s ", argv[i]);
	}
	printf("\n");
	printf("this the nflag: %d, log: %d\n", nflag, log);

	if(nflag && log){
		for(int i = 1; i < argc; ++i) {
			if(strcmp("-l", argv[i]) == 0){
				logFile= argv[i+1];
				int fd2 = open(logFile, O_CREAT | O_TRUNC, S_IRWXU);
				close(fd2);
			}
			if(strcmp("-N", argv[i]) == 0){
				N= atoi(argv[i+1]);
			}
		}
		if (strcmp(argv[5],"localhost") == 0){
		//will connect to default IP address
			printf("found local host: %s\n", argv[5]);
			address.sin_addr.s_addr = INADDR_ANY;
		}else{
			printf("local host not found %s\n", argv[5]);
			address.sin_addr.s_addr = inet_addr(argv[5]);
		}
		if(argc == 7){
			address.sin_port = htons( atoi(argv[6]) );
			printf("found port number:%d \n", atoi(argv[6]));
		}
		else{
			printf("default port number \n");
			address.sin_port = htons( PORT );
		}
	}
	else if(nflag){
		for(int i = 1; i < argc; ++i) {
			if(strcmp("-N", argv[i]) == 0){
				N= atoi(argv[i+1]);
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
	printf("This is N: %zu\n", N);
	struct thread_arguments *arguments = (thread_arguments*)malloc(sizeof(thread_arguments));
	arguments->log = log;
	arguments->logFile = logFile;
	
	pthread_t thread_id[N];
	for(size_t n = 0; n < N; ++n){
		printf("this is [n]: %zu\n", n);
		pthread_create(&thread_id[n], NULL, &client_reqs, (void*)arguments);
	}

	while(1){
		printf("Top of loop\r\n"); 
		//accept the client connection 
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		}
		//control queue push
		pthread_mutex_lock(&lock);
		requests.push(new_socket);
		printf("Pushed to queue: %d\n", new_socket);
		pthread_mutex_unlock(&lock); 
		//signal waiting thread that a request is in queue
		pthread_cond_signal(&conditional);

	} 
	close(server_fd);
	return 0; 
} 

// called from pthread_create()
void *client_reqs(void* parameters){ //mini program
	
	while(1){
		int new_socket = queue_socket_id();
		printf("Accepted from queue: %d\n", new_socket);
		struct thread_arguments *arguments = (thread_arguments*)parameters;
		arguments->sock_id = new_socket;
		//can now do get and put requests
		process_requests(arguments);
	}

	return 0;
}

//function to synchronize the global queue
int queue_socket_id(){
	pthread_mutex_lock(&lock);
	printf("This is queue empty: %d\n", requests.empty());
	if(requests.empty()){
		// this waits for a signal to know that we can pop from the queue
		pthread_cond_wait(&conditional, &lock);
	}
	
	int sock_id = requests.front();
	requests.pop();
	printf("Popped from queue: %d\n", sock_id);
	pthread_mutex_unlock(&lock);

	return sock_id;
}


//calls Get and put functions
void process_requests(void* parameters){

	ssize_t readCount; 
	char buffer[1024] = {0};
	char hexbuf[1024] = {0};
	int64_t num = 0;
	uint64_t log_offset;
	// read the client request
	struct thread_arguments *arguments = (thread_arguments*)parameters;
	int new_socket = arguments->sock_id;
	bool log = arguments->log;
	const char* logFile = arguments->logFile;
	readCount = read(new_socket , buffer, sizeof(buffer));
	printf("This is the buffer: %s\n",buffer ); 
	//command is a get or put request
	//filename is the name of the file read in from the client
	//http is used for the reponse
	char command[50], filename[50], http[50];
	int64_t content_length = 0;
	char* nl_split = NULL;
	//split the get and put requests on the new line character.
	nl_split = strtok(buffer, "\r\n");
	// Im going to check the first token to find
	// the request and the filename requested.
	int scan =sscanf(nl_split, "%s %s %s", command, filename, http);
	printf("This is the scan: %i\n",scan ); 
	printf("http: %s\n", http);
	while (nl_split != NULL)
	{
		//Loop to find content length
		int scan1 = sscanf(nl_split, "Content-Length:%ld", &content_length);
		printf("This is the scan1: %i\n",scan1 ); 
		nl_split = strtok(NULL, "\r\n");
	}
	printf("This is the content_length: %ld\n",content_length );  
	arguments->filename = filename;
	arguments->command = command;
	arguments->http = http;
	arguments->content_length = content_length;
	
	//Status Code 500
	if(!(strcmp(command,"GET")==0 || strcmp(command,"PUT")==0)){
		if(log){
			pthread_mutex_lock(&lock);
			log_offset = global_log_offset;
			num = sprintf(hexbuf, "FAIL: %s %s HTTP/1.1 --- response 500\n========\n", command, filename);
			global_log_offset += num;
			printf("this is num: %ld\n", num);
			printf("this is arguments->log_offset: %lu\n", log_offset);
			printf("this is global_log_offset: %lu\n", global_log_offset);
			pthread_mutex_unlock(&lock); 
			int fd2 = open(logFile, O_WRONLY, S_IRWXU);
			pwrite(fd2, hexbuf, num, log_offset);
			close(fd2);
			dprintf(new_socket, "%s 500 Internal Server Error\r\n", http);
		}
		else{
			dprintf(new_socket, "%s 500 Internal Server Error\r\n", http);
		}
		free(arguments);
		close(new_socket);
		return;
	}
	if(invalid_name(filename)){
		if (log){
			pthread_mutex_lock(&lock); 
			log_offset = global_log_offset;
			num = sprintf(hexbuf, "FAIL: %s %s %s --- response 400\n========\n", command, filename, http);
			global_log_offset += num;
			printf("this is num: %ld\n", num);
			printf("this is arguments->log_offset: %lu\n", log_offset);
			printf("this is global_log_offset: %lu\n", global_log_offset);
			pthread_mutex_unlock(&lock); 
			int fd2 = open(logFile, O_WRONLY, S_IRWXU);
			pwrite(fd2, hexbuf, num, log_offset);
			close(fd2);
			dprintf(new_socket, "%s 400 Bad Request\r\n", http);
			dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
		}
		else{
			dprintf(new_socket, "%s 400 Bad Request\r\n", http);
			dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
		}
		free(arguments);
		close(new_socket);
		return;
	}

	//GET Requests
	if (strcmp(command,"GET")==0){
		content_length = getFileSize(arguments);
		if(!(content_length == 0)){
			arguments->content_length = content_length;
			get(arguments);
		}
		free(arguments);
		close(new_socket);
	}
	//PUT Requests
	else if(strcmp(command,"PUT") ==0){
		put(arguments);
		free(arguments);
		close(new_socket);
	}


	return;
}

void get(void* parameters){
	struct thread_arguments *arguments = (thread_arguments*)parameters;
	char* filename = arguments->filename;
	int new_socket = arguments->sock_id;
	int64_t content_length = arguments->content_length;
	int64_t content = arguments->content_length;
	bool log = arguments->log;
	char* logFile = arguments->logFile;
	int64_t num = 0;
	char* http = arguments->http;
	char hexbuf[1024] = {0}; 
	ssize_t  read_count = 1, sent = 1;
	//second buffer to be able to read and write files
	char buf[32] = {0}; 
	uint64_t log_offset;
	if(log){
		pthread_mutex_lock(&lock); 
		log_offset = global_log_offset;
		num = sprintf(hexbuf, "GET %s length 0\n========\n", filename);
		global_log_offset += num;
		printf("this is num: %ld\n", num);
		printf("this is arguments->log_offset: %lu\n", log_offset);
		printf("this is global_log_offset: %lu\n", global_log_offset);
		pthread_mutex_unlock(&lock); 
		int fd2 = open(logFile, O_WRONLY, S_IRWXU);
		pwrite(fd2, hexbuf, num, log_offset);
		close(fd2);
		dprintf(new_socket, "%s 200 OK\r\n", http);
		dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content);
	}
	else{
		dprintf(new_socket, "%s 200 OK\r\n", http);
		dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content);

	}
	int fd = open(filename, O_RDONLY, S_IRWXU);
	printf("GET: This is the new_socket: %d\n",new_socket );  
	printf("GET: This is the fd: %d\n",fd );  
	while(content_length > 0){
		read_count = read(fd, buf, sizeof(buf));
		sent = send(new_socket , buf, read_count , 0 ); 
		content_length -= sent;
		if(read_count != sent){
			dprintf(new_socket, "%s 500 Internal Server Error\r\n", http);
		}
	}
	close(fd);
	printf("End of get\n");
}

void put(void* parameters){
	struct thread_arguments *arguments = (thread_arguments*)parameters;
	char* filename = arguments->filename;
	int new_socket = arguments->sock_id;
	uint64_t content_length = arguments->content_length;
	char* http = arguments->http;
	char* command = arguments->command;
	bool log = arguments->log;
	char* logFile = arguments->logFile;
	uint64_t log_offset;
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
	printf("This is the fd: %i\n",fd ); 
	close(fd);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

	if (fd < 0){
		printf(" Value of errno: %d\n ", errno); 
		printf("The error message is : %s\n",  strerror(errno)); 
		if (errno == EACCES){
			if (log){
				num = sprintf(hexbuf, "FAIL: %s %s %s --- response 403\n========\n", command, filename, http);
				pthread_mutex_lock(&lock); 
				log_offset = global_log_offset;
				global_log_offset +=num;
				printf("this is num: %ld\n", num);
				printf("PUT: this is arguments->log_offset: %lu\n", log_offset);
				printf("this is global_log_offset: %lu\n", global_log_offset);
				pthread_mutex_unlock(&lock); 
				int fd2 = open(logFile, O_WRONLY, S_IRWXU);
				pwrite(fd2, hexbuf, num, log_offset);
				log_offset+=num;
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
	if(log){
		num = sprintf(hexbuf, "%s %s length %li\n", command, filename, content_length);
		pthread_mutex_lock(&lock); 
		log_offset = global_log_offset;
		//calculate put size
		global_log_offset += ((content_length /20)*69) + ((content_length % 20) *3) +10 + 9 + num;
		printf("this is num: %ld\n", num);
		printf("PUT: this is arguments->log_offset: %lu\n", log_offset);
		printf("this is global_log_offset: %lu\n", global_log_offset);
		pthread_mutex_unlock(&lock); 
		int fd2 = open(logFile, O_WRONLY, S_IRWXU);
		number = pwrite(fd2, hexbuf, num, log_offset);
		log_offset+=num;
		uint64_t counter = 0;
		uint64_t content = content_length;
		while(content_length >0 && read_count > 0 && counter < content){
			read_count = recv(new_socket , buf, sizeof(buf), 0); 
			num = sprintf(hexbuf, "%08lu ", counter);
			number = pwrite(fd2, hexbuf, num, log_offset);
			log_offset += num;
			for(ssize_t i =0; i < read_count; ++i ){
				num = sprintf(hexbuf, "%02x ", buf[i]);
				number = pwrite(fd2, hexbuf, num, log_offset);
				log_offset += num;
			}
			num = sprintf(hexbuf, "\n");
			number = pwrite(fd2, hexbuf, num, log_offset);
			log_offset += num;
			write_count = write(fd, buf, read_count);
			counter+=20;
			content_length -= write_count;
		}
		num = sprintf(hexbuf, "========\n");
		number = pwrite(fd2, hexbuf, num, log_offset);
		log_offset += num;
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

int64_t getFileSize(void* parameters){
	struct thread_arguments *arguments = (thread_arguments*)parameters;
	char* filename = arguments->filename;
	int new_socket = arguments->sock_id;
	bool log = arguments->log;
	char* logFile = arguments->logFile;
	char* http = arguments->http;
	char hexbuf[1024] = {0};
	int64_t num = 0;
	uint64_t log_offset;
	int64_t content_length = 0;
	int fd = open(filename, O_RDONLY, S_IRWXU);
	if (fd < 0){
		printf(" Value of errno: %d\n ", errno); 
		printf("The error message is : %s\n",  strerror(errno)); 
		if(errno == 2){
			if (log){
				pthread_mutex_lock(&lock); 
				num  = sprintf(hexbuf, "FAIL: GET %s %s --- response 404\n========\n", filename, http);
				log_offset = global_log_offset;
				global_log_offset += num;
				printf("this is num: %ld\n", num);
				printf("this is arguments->log_offset: %lu\n", log_offset);
				printf("this is global_log_offset: %lu\n", global_log_offset);
				pthread_mutex_unlock(&lock); 
				int fd2 = open(logFile, O_WRONLY, S_IRWXU);
				pwrite(fd2, hexbuf, num, log_offset);
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
				pthread_mutex_lock(&lock); 
				num = sprintf(hexbuf, "FAIL: GET %s %s --- response 403\n========\n", filename, http);
				log_offset = global_log_offset;
				global_log_offset += num;
				printf("this is num: %ld\n", num);
				printf("this is arguments->log_offset: %lu\n", log_offset);
				printf("this is global_log_offset: %lu\n", global_log_offset);
				pthread_mutex_unlock(&lock); 
				int fd2 = open(logFile, O_WRONLY, S_IRWXU);
				pwrite(fd2, hexbuf, num, log_offset);
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
	printf("File_size: This is the content_length: %ld\n",content_length );
	close(fd);
	return content_length;
}

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

