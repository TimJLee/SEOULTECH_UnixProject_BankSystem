#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

int i_ok=1;
int j_ok=1;


int main(int argc, char **argv[])
{


char buf[1];
int arr_fd = open(argv[1], O_RDONLY);
int wait_fd = open(argv[2], O_RDONLY);

pid_t pid;



while(1)
{
//printf("arr : %d\n",arr[i]);
//printf("wiat : %d\n",wait[j]);
//printf("%d\n",i_ok);



arr_fd = open(argv[1], O_RDONLY);
read(arr_fd,buf,1);
i_ok = buf[0] -'0';
close(arr_fd);

wait_fd = open(argv[2], O_RDONLY);
read(wait_fd,buf,1);
j_ok = buf[0] - '0';
close(wait_fd);

//printf("%d\n",i_ok);


pid = fork();

if(pid == 0 && i_ok)
{
arr_fd = open(argv[1], O_WRONLY);
i_ok = 0;
write(arr_fd,"0",1);
close(arr_fd);
printf("arr 실행\n");
execl("/home/lavi/project/arr", "arr", argv[1]);
printf("arr 실패\n");
}

sleep(1);

if(pid == 0 && j_ok)
{

j_ok = 0;
wait_fd = open(argv[2], O_WRONLY);
write(wait_fd,"0",1);
close(wait_fd);
printf("wait 실행\n");
execl("/home/lavi/project/wait","wait",argv[2]);
printf("wait 실패\n");
}

else if(pid == 0)
_exit(0);


sleep(1);



/*
if( pid == 0 && (i_ok || j_ok))
{
if(i_ok)
i_ok = 0;

else if(j_ok)
j_ok = 0;


if(i_ok == 0)
{
sleep(2);
printf("arr  Complete\n");
arr[i++] = -1;
i_ok =1;
}

else if(j_ok == 0)
{
sleep(4);
printf("wait  Complete\n");
wait[j++] = -1;
j_ok=1;
}


_exit(0);

}*/



}



}



