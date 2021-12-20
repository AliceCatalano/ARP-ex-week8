#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
int sender,  receiver;

char portno[]={'6', '9', '6','9','\0'};

char ipadress[]={'1', '2', '7','.','0','.','0','.','1','\0'};
char receiverPIDstr[5];
int main(){
    sender = fork();
    if (sender==0){
    /*
    Should exec the sender process
    */
    char * arg_list_1[] = { "/usr/bin/konsole",  "-e", "./sender",(char*)portno, (char*)NULL };
    execvp ("/usr/bin/konsole", arg_list_1);
  }

  else{
     pid_t receiver_pid = fork();
     if(receiver_pid==0){
       /*
       Should exec the receiver process
       */
      char * arg_list_2[] = { "/usr/bin/konsole",  "-e", "./receiver",(char*)ipadress, (char*)portno,(char*)NULL };
      execvp ("/usr/bin/konsole", arg_list_2);
      
     }
  return 0;
  }
}