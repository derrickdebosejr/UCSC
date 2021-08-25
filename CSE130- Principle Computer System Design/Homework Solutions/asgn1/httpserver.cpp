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
//from the geeks for ge
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

#define LISTEN_BL 10
#define PORT 80

void get(char filename[], int new_socket, int64_t content_length);
void put(char filename[], int new_socket, int64_t content_length, char http[]);
int64_t getFileSize(char filename[], int new_socket, char http[]);
bool invalid_name(char filename[]);


//Some of this code comes from the section slides.
int main(int argc, const char *argv[]){ 
	int server_fd, new_socket;
	ssize_t readCount; 
	struct sockaddr_in address; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 

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
	if (argc==2){
		if (strcmp(argv[1],"localhost") == 0){
			//will connect to default IP address
			address.sin_addr.s_addr = INADDR_ANY;
		}
		else{
			//will connect to the given proper IP address
			address.sin_addr.s_addr = inet_addr(argv[1]); 
		}
	}
	// This assigns the port number for the server
	if (argc == 3){
		address.sin_port = htons( atoi(argv[2]) ); 
	} else{
		address.sin_port = htons( PORT );
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
	while(1){
		printf("HERE\r\n"); 
		//accept the client connection 
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
						   (socklen_t*)&addrlen))<0) 
		{ 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		}
		// read the client request
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
		if(invalid_name(filename)){
			dprintf(new_socket, "%s 400 Bad Request\r\n", http);
			close(new_socket);
			continue;
		}
		//GET Requests
		if (strcmp(command,"GET")==0){
			content_length = getFileSize(filename, new_socket, http);
			get(filename, new_socket, content_length);
			//send(new_socket , contents, sizeof(contents) , 0 ); 
		}
		//PUT Requests
		else if(strcmp(command,"PUT") ==0){
			//S_IRWXU used to fix problem with files being created
			put(filename, new_socket, content_length, http);
			dprintf(new_socket, "Content-Length:0\r\n");
			//int send1 = send(new_socket , httpString, sizeof(httpString) , 0 );
			//printf("This is the send1: %d\n",send1 );
		}
		//Status Code 500
		else{
			dprintf(new_socket, "%s 500 Internal Server Error\r\n", http);
			close(new_socket);
			continue;
		}
		close(new_socket);
	} 
	close(server_fd);
	return 0; 
} 


void get(char filename[], int new_socket, int64_t content_length){
	ssize_t  read_count = 1, sent = 1;
	//second buffer to be able to read and write files
	char buf[32] = {0}; 
	//dprintf(new_socket, "Content-Length: %ld\r\n ", content_length);
	int fd = open(filename, O_RDONLY, S_IRWXU);
	printf("This is the new_socket: %d\n",new_socket );  
	printf("This is the fd: %d\n",fd );  
	//int64_t content_length =0;
	while(content_length > 0){
		read_count = read(fd, buf, sizeof(buf));
		//printf("This is the read_count: %zd\n",read_count ); 
		//printf("This is the content_length: %i\n",content_length );
		sent = send(new_socket , buf, read_count , 0 ); 
		content_length -= sent;
	}
	close(fd);
}

void put(char filename[], int new_socket, int64_t content_length, char http[]){
	int fd = 0;
	ssize_t read_count = 1, write_count = 1;
	char buf[32] = {0}; 
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
			dprintf(new_socket, "%s 403 Forbidden\r\n", http);
		}
		close(fd);
		return;
	}
	//printf("This is the new_socket: %i\n",new_socket ); 
	while(content_length >0){
		read_count = recv(new_socket , buf, sizeof(buf), 0); 
		write_count = write(fd, buf, read_count);
		content_length -= write_count;
	}
	if(status== 201){
		dprintf(new_socket, "%s %i Created\r\n" , http, status);
	}else{
		dprintf(new_socket, "%s %i OK\r\n" , http, status);
	}
	close(fd);
}

int64_t getFileSize(char filename[], int new_socket, char http[]){
	int64_t content_length = 0;
	int fd = open(filename, O_RDONLY, S_IRWXU);
	if (fd < 0){
		printf(" Value of errno: %d\n ", errno); 
		printf("The error message is : %s\n",  strerror(errno)); 
		if(errno == 2){
			dprintf(new_socket, "%s 404 File Not Found\r\n", http);
			dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
		}else if (errno == EACCES){
			dprintf(new_socket, "%s 403 Forbidden\r\n", http);
			dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
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
	dprintf(new_socket, "%s 200 OK\r\n", http);
	dprintf(new_socket, "Content-Length: %ld\r\n\r\n", content_length);
	printf("This is the content_length: %ld\n",content_length );
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


