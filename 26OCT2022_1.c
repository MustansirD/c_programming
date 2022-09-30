#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//getpid,read,write
#include<fcntl.h>//open

#define SEQFILE "num"
#define MAXBUFF 100

int main()
{
  int fd,i,n,pid,num;
  char buff[MAXBUFF + 1];

  pid = getpid();
  fd = open(SEQFILE,2);
  if (fd < 0)
  {
    printf("cannot open file [%s]\n",SEQFILE);
    exit(1);
  }
 
  printf("-----pid=[%d],fd=[%d]-----\n",pid,fd);

  for(i=0;i<20;i++)
  {
    lseek(fd,0L,0);
    n = read(fd,buff,MAXBUFF);
    if(n<=0)
    {
      printf("read error\n");
      exit(1);
    }
    buff[n] = '\0';

    n = sscanf(buff,"%d\n",&num);
    if( n != 1)
    {
      printf("sscanf error\n");
      exit(1);
    }

    printf("pid=[%d],num=[%d]\n",pid,num);
    num++; /* increment the sequence number */
    sprintf(buff,"%03d\n",num);
    n = strlen(buff);
    lseek(fd,0L,0);
    if ( write(fd,buff,n) != n)
    {
      printf("write error\n");
      exit(1);
    }
  }
  close(fd);
}
