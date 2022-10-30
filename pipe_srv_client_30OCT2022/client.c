#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define	MAX_BUFFER_SIZE 256

void clientRequest(int read_fd,int write_fd)
{
  char Buffer[MAX_BUFFER_SIZE];
  int len,result;
  
  memset(Buffer,0,sizeof(Buffer));
  //Read file name from stdin
  scanf("%s",Buffer);
  getchar();
  
  len = strlen(Buffer);
  
  result=write(write_fd,Buffer,len);
  if(result != len)
  {
    printf("write error\n");
    exit(1);
  }

  memset(Buffer,0,sizeof(Buffer));
  result = read(read_fd,Buffer,MAX_BUFFER_SIZE);
  
  if(result > 0)
  {
    write(1,Buffer,result);
  }
}
