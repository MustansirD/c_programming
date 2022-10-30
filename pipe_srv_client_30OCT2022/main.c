#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>//open
#include<sys/wait.h>//wait

#define MAX_BUFFER_SIZE 256

void clientRequest(int read_fd,int write_fd);
void serverResponse(int read_fd,int write_fd);

int main()
{
  int pipe_1[2];
  int pipe_2[2];
  int childPid;

  if(pipe(pipe_1) != 0 )
  {
    printf("pipe_1 create error\n");
    exit(1);
  }

  if(pipe(pipe_2) != 0 )
  {
    printf("pipe_2 create error\n");
    exit(1);
  }

  childPid = fork();
  if( childPid < 0 )
  {
    printf("fork error\n");
    exit(1);
  }

  if(childPid > 0 )//Parent execution block
  {
    printf("Inside Parent Execution Block\n");

    close(pipe_1[0]);//In parent we will close read end of pipe_1
    close(pipe_2[1]);//In parent we will close write end of pipe_2
    /*
      We are doing the above operations
      as in parent process we will write using pipe_1
      and read using pipe_2.
    */
   clientRequest(pipe_2[0],pipe_1[1]);

   wait(NULL);
   printf("Inside Parent execution block - Child Terminated\n");
  }
  else//child execution block
  {
    printf("Inside Child Execution Block\n");

    close(pipe_1[1]);//In child process we will close the write end of pipe_1
    close(pipe_2[0]);//In child process we will close the read end of pipe_2
    /*
      We are doing the above operations
      as in child process we will rcv request from process
      and read it using read end of pipe_1 and 
      write using pipe_2
    */

   serverResponse(pipe_1[0],pipe_2[1]);

  }


}
