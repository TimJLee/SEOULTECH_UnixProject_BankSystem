#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<fcntl.h>

#define KYE_NUM_1 9527
#define KYE_NUM_2 9528
#define KYE_NUM_3 9529
#define KYE_NUM_4 9530
#define MEM_SIZE 1024


typedef struct element
{
int name;
int good;
}element;

typedef struct _queue
{
element a[200];
int count;
int using;
}queue;


int main(int argc, char **argv[])
{


int i=0;
int j=0;

int shm_id_1;
queue *wait_1;

int shm_id_2;
queue *wait_2;


//공유메모리 생성
shm_id_1 = shmget((key_t)KYE_NUM_1,MEM_SIZE,IPC_CREAT|0666);
shm_id_2 = shmget((key_t)KYE_NUM_2,MEM_SIZE,IPC_CREAT|0666);


//공유메모리첨부
wait_1 = shmat(shm_id_1,0,0);
wait_2 = shmat(shm_id_2,0,0);


//초기화
wait_1->count = 3;
wait_1->using =0;
wait_2->count = 4;
wait_2->using = 0;


(wait_1->a[0]).good = 9;
wait_1->a[1].good = 9;


wait_2->a[0].good = 9;
wait_2->a[1].good = 9;

//fork문을 통해 병렬연산을 하지만 실제로는 fork문 하나를 생성시키고 그 하나의 포크문이 굉장히 빨리 돌도록 해서
//병렬연산을 실행하는것

pid_t pid;

while(wait_1->count <4 || wait_2->count<5)
{

printf("wait _1, %d\n",wait_1->a[0].good);
printf("wait _1, %d\n",wait_1->a[1].good);

printf("wait _2, %d\n",wait_2->a[0].good);
printf("wait _2, %d\n",wait_2->a[1].good);

//공유메모리 생성
shm_id_1 = shmget((key_t)KYE_NUM_1,MEM_SIZE,IPC_CREAT|0666);
shm_id_2 = shmget((key_t)KYE_NUM_2,MEM_SIZE,IPC_CREAT|0666);


//공유메모리첨부
wait_1 = shmat(shm_id_1,0,0);
wait_2 = shmat(shm_id_2,0,0);

pid = fork();

if(pid == 0 && wait_1->count != 0 && wait_1->using == 0)
{
wait_1->using =1;
sleep(5);
wait_1->a[0].good = 1;
wait_1->a[1].good = 2;


printf("wait_1 Complete\n");
wait_1->using =0;
exit(0);
}

sleep(0.3);

if(pid == 0 && wait_2->count !=0 &&wait_2->using ==0)
{
wait_2->using =1;
sleep(7);
wait_2->a[0].good = 1;
wait_2->a[1].good = 2;

wait_2->using =0;
printf("wait_2 Complete\n");
exit(0);
}

else if(pid == 0)
exit(0);


sleep(1);

}



}



