#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    while(1){
    int sockfd, portno, n;

    struct sockaddr_in send_addr;
    struct hostent *sender;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //function to initialize the socket
    if (sockfd < 0) // returns -1 if error detected
        error("ERROR opening socket");
    sender = gethostbyname(argv[1]); //second element of argv array, the name of the sender
    if (sender == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &send_addr, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    bcopy((char *)sender->h_addr, 
         (char *)&send_addr.sin_addr.s_addr,
         sender->h_length);
    send_addr.sin_port = htons(portno);
    //communication with the sender
    if (connect(sockfd,(struct sockaddr *)&send_addr,sizeof(send_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    }
    n = write(sockfd,buffer,strlen(buffer)); //send something to the sender
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
   
    n = read(sockfd,buffer,255); //confirm of the message recived.
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
}
