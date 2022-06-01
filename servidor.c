#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <time.h>

/* the port users will be connecting to */
#define MYPORT 8000

/* how many pending connections queue will hold */
#define BACKLOG 10

void date(int new_fd);
void pwd(int new_fd);
void whoami(int new_fd);


int main(int argc, char *argv[ ]){
  /* listen on sock_fd, new connection on new_fd */
  int sockfd, new_fd, numbytes;

  /* my address information */
  struct sockaddr_in my_addr;

  /* connectors address information */
  struct sockaddr_in their_addr;
  int sin_size;
  // max number of bytes we can get at once
  #define MAXDATASIZE 300
  char buf[MAXDATASIZE];

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("Server-socket() error lol!");
    exit(1);
  }
  else
    printf("Server-socket() sockfd is OK...\n");

  /* host byte order */
  my_addr.sin_family = AF_INET;

  /* short, network byte order */
  my_addr.sin_port = htons(MYPORT);

  /* automatically fill with my IP */
  my_addr.sin_addr.s_addr = INADDR_ANY;
  printf("Server-Using %s and port %d...\n", inet_ntoa(my_addr.sin_addr), MYPORT);

  /* zero the rest of the struct */memset(&(my_addr.sin_zero), '\0', 8);
  if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
    perror("Server-bind() error");
    exit(1);
  }
  else
    printf("Server-bind() is OK...\n");

  if(listen(sockfd, BACKLOG) == -1){
    perror("Server-listen() error");
    exit(1);
  }

  printf("Server-listen() is OK...Listening...\n");

  sin_size = sizeof(struct sockaddr_in);
  while(1)
  {
    if((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1){
      perror("Server-accept() error");
      exit(1);
    }

    printf("Server-accept() is OK...\n");
    printf("Server-new socket, new_fd is OK...\n");
    printf("Server: Got connection from %s\n", inet_ntoa(their_addr.sin_addr));

    if((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1){
    
      perror("recv()");
      exit(1);
    }
    else
      printf("Servidor-The recv() is OK...\n");
	
    buf[numbytes] = '\0';
    printf("Servidor-Received: %s\n", buf);
   
    //comandos
    if(strcmp(buf, "date") == 0)
    	date(new_fd);
    		
    		
    if(strcmp(buf, "pwd") == 0)
    	pwd(new_fd);
    	
    if(strcmp(buf, "whoami") == 0)
    	whoami(new_fd);
    	
    
    else{
    if(send(new_fd, "Error comando", MAXDATASIZE, 0) == -1)
    		perror("Server-send() error lol!");
  	//else
    	//printf("Server-send is OK...!\n");
    //---

	}

    close(new_fd);
    printf("Server-new socket, new_fd closed successfully...\n");
  }
  close(sockfd);
  return 0;
}


void date(int new_fd){
time_t current_time;
	    char* c_time_string;

	    /* Obtain current time. */
	    current_time = time(NULL);

	    if (current_time == ((time_t)-1))
	    {
		(void) fprintf(stderr, "Failure to obtain the current time.\n");
		exit(EXIT_FAILURE);
	    }

	    /* Convert to local time format. */
	    c_time_string = ctime(&current_time);
    	   send(new_fd, c_time_string, 300, 0);
}


void pwd(int new_fd){
    char path[300];
    getcwd(path, 300);
    //printf("Current working directory: %s\n", path);
     send(new_fd, path, 300, 0);

}



void whoami(int new_fd){
	char *buf;
	buf=(char *)malloc(10*sizeof(char));
	buf=getlogin();
	//printf("\n %s \n",buf);
	send(new_fd, buf, 300, 0);

}
