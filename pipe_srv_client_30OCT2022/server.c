#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/file.h>

#define MAX_BUFFER_SIZE 256

void serverResponse(int read_fd,int write_fd)
{
  char Buffer[MAX_BUFFER_SIZE];
  int result,fd;

  result = read(read_fd,Buffer,MAX_BUFFER_SIZE);
  Buffer[result] = '\0';
  
  fd = open(Buffer,O_RDONLY);
  if(fd < 0)
  {
    printf("open error\n");
    exit(1);
  } 

  memset(Buffer,0,sizeof(Buffer));
  result = read(fd,Buffer,MAX_BUFFER_SIZE);
  result = write(write_fd,Buffer,MAX_BUFFER_SIZE);
  
}
