#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char **argv[])
{

int i_ok;

int fd;
char buf[1];

printf("넘어왔다");

fd = open(argv[1], O_RDWR);
write(fd,"0",1);
close(fd);

sleep(5);
//printf("%d\n",*i_ok);
printf("arr Complete\n");

fd = open(argv[1], O_RDWR);
write(fd,"1",1);
close(fd);




return 0;
}
