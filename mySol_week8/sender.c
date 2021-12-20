#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}
void dostuff (int sock)
{
   int n;
   char buffer[256];
      
   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");
   printf("Here is the message: %s\n",buffer);
   n = write(sock,"I got your message",18);
   if (n < 0) error("ERROR writing to socket");
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, receiver, pid;
     
     char buffer[256];
     struct sockaddr_in send_addr, reciv_addr; //structs that save all the data about the server and the client
     int n;
     
     if (argc < 2) { //
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0); // function that define thesicket saves the output in the fd
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     bzero((char *) &send_addr, sizeof(send_addr)); //erases data location pointed by the first element
     
     portno = atoi(argv[1]); //taking the port number
     send_addr.sin_family = AF_INET;
     send_addr.sin_addr.s_addr = INADDR_ANY;
     send_addr.sin_port = htons(portno); //we have to care, we take it from argv 
   //second socket action
   if (bind(sockfd, (struct sockaddr *) &send_addr, sizeof(send_addr)) < 0) // the struct has the port number
              error("ERROR on binding");
     //third action of the socket
     listen(sockfd,5); 
     receiver = sizeof(reciv_addr);
    while(1){
     //fourth socket action
     newsockfd = accept(sockfd, (struct sockaddr *) &reciv_addr, &receiver); // it's the first time we see this varaible
     if (newsockfd < 0)  //here there's the communication with the client
          error("ERROR on accept");
     pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
        
    }
}




