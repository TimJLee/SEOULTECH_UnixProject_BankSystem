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

int arr[5] = {-1,1,2,3,4};
int wait[4] = {-1,5,6,7};
int i=0;
int j=0;

int switch_i = 1;
int switch_j = 1;

//Status Table
//ok || switch

//02 --> wait
//13 --> Complete
//11 --> Start


//부모 프로세스가 넘어올때 이중으로 실행되는것을 막기위해 상태도 작성함
//fork문을 통해 병렬연산을 하지만 실제로는 fork문 하나를 생성시키고 그 하나의 포크문이 굉장히 빨리 돌도록 해서
//병렬연산을 실행하는것

pid_t pid;

while(i<5 || j<4)
{


arr_fd = open(argv[1], O_RDONLY);
read(arr_fd,buf,1);
i_ok = buf[0] -'0';
close(arr_fd);

wait_fd = open(argv[2], O_RDONLY);
read(wait_fd,buf,1);
j_ok = buf[0] - '0';
close(wait_fd);


//실행완료
if(i_ok == 1 && switch_i == 3)
{
switch_i = 1;
} 

//실행중
else if(i_ok == 0 && switch_i ==2)
{
switch_i = 3;
}


//실행
if(i_ok == 1 && switch_i == 1)
{
switch_i = 2;
// i Buffer에 실행되기전에 해야할일 큐값 빼내기
i++;

}



//실행완료
if(j_ok == 1 && switch_j == 3)
{
switch_j = 1;
} 

//실행중
else if(j_ok == 0 && switch_j ==2)
{
switch_j = 3;
}


//실행 때문에 if문 바꿈
//실행
if(j_ok == 1 && switch_j == 1)
{
switch_j = 2;
// i Buffer에 실행되기전에 해야할일 큐값 빼내기
j++;

}


pid = fork();

if(pid == 0 && i_ok && i<5)
{
arr_fd = open(argv[1], O_WRONLY);
i_ok = 0;
write(arr_fd,"0",1);
close(arr_fd);

printf("arr %d 실행\n",arr[i]);
/*execl("/home/lavi/project/arr", "arr", argv[1]);
printf("arr 실패\n");*/

sleep(5);
//printf("%d\n",*i_ok);
printf("arr Complete\n");

int fd = open(argv[1], O_RDWR);
write(fd,"1",1);
close(fd);

exit(0);
}

sleep(1);

if(pid == 0 && j_ok && j<4)
{
j_ok = 0;
wait_fd = open(argv[2], O_WRONLY);
write(wait_fd,"0",1);
close(wait_fd);


printf("wait %d 실행\n", wait[j]);
/*execl("/home/lavi/project/wait","wait",argv[2]);
printf("wait 실패\n");*/

sleep(7);
printf("wait Complete\n");

int fd = open(argv[2], O_RDWR);
write(fd,"1",1);
close(fd);
exit(0);

}

else if(pid == 0)
exit(0);


sleep(1);

}



}



