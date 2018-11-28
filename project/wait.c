#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>


int main(int argc, char **argv[])
{

int fd;
char buf[1];

fd = open(argv[1], O_RDWR);
write(fd,"0",1);
close(fd);

sleep(7);
printf("wait Complete\n");

fd = open(argv[1], O_RDWR);
write(fd,"1",1);
close(fd);
return 0;

}
