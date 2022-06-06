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
    printf("Servidor-Received: %s \n", buf);
   
	printf("\n");
	
//----------------------------------


//char buf[300];
char path[300];
char cadena[1000];
FILE *fp;
FILE *pf;




//Guarda en el apuntador lo que arroja la terminal
fp = popen(buf, "r");

	

memset(cadena, '\0', strlen(cadena));//Limpia la cadena

	
//Guarda los datos en el archivo
if (!(pf=fopen("comando.txt","w"))) /* controlamos si se produce un error */
{
	printf("Error al abrir el fichero");
	exit(0); /* abandonamos el programa */
}
else 
{
	//Guardamos los datos en el archivo
	while (fgets(path, 300, fp) != NULL)
	fputs(path,pf);
	fclose(pf);
}
pclose(fp);


//Guarda en una variable lo que tiene el arcvhivo
  FILE * stream;
  stream = fopen("comando.txt", "r");
  int count = fread(cadena, sizeof(char), 1000, stream);
  fclose(stream);
  //Imprime
  printf(" %s \n", cadena);
  
 //Envia la cadena
if(send(new_fd, cadena, strlen(cadena), 0)==-1)
	printf("Error\n");
else
	printf("Enviado\n");

//------------------------	
	
	
	


//Cierra el socket
    close(new_fd);
    printf("Server-new socket, new_fd closed successfully...\n");
    
  }
  close(sockfd);
  return 0;
}


