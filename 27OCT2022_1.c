#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//getpid,read,write
#include<fcntl.h>//open
#include<sys/file.h>//flock 

#define SEQFILE "seqno"
#define MAXBUFF 100

void myLock(int fd)
{
  int result;
  result = flock(fd,LOCK_EX);
  if(result != 0 )
  {
    printf("flock error\n");
    exit(1);
  }
}

void myUnlock(int fd)
{
  int result;
  result = flock(fd,LOCK_UN);
  if(result != 0 )
  {
    printf("flock release error\n");
    exit(1);
  }

}


int main()
{
  int fd,i,n,pid,seqno;
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
    myLock(fd);
    lseek(fd,0L,0);
    n = read(fd,buff,MAXBUFF);
    if(n<=0)
    {
      printf("read error\n");
      exit(1);
    }
    buff[n] = '\0';

    n = sscanf(buff,"%d\n",&seqno);
    if( n != 1)
    {
      printf("sscanf error\n");
      exit(1);
    }

    printf("pid=[%d],seq#=[%d]\n",pid,seqno);

    seqno++; /* increment the sequence number */
    sprintf(buff,"%03d\n",seqno);
    n = strlen(buff);
    lseek(fd,0L,0);
    if ( write(fd,buff,n) != n)
    {
      printf("write error\n");
      exit(1);
    }

    myUnlock(fd);

  }
  close(fd);
}
