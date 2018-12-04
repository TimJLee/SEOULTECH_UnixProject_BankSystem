#include "bank.h"

#define KYE_NUM_1 9527
#define KYE_NUM_2 9528
#define KYE_NUM_3 9529
#define KYE_NUM_4 9530
#define KYE_NUM_5 9531
#define MEM_SIZE 10000

int main(int argc, char **argv[])
{
FILE *fp;
fp = fopen("data.txt", "r+");

int shm_id_1;
QueueType *wait_1;

int shm_id_2;
QueueType *wait_2;

int shm_id_3;
QueueType *wait_3;

int shm_id_4;
QueueType *wait_4;

int shm_id_5;
QueueType *complete;

int arr_account[30]={0};


//공유메모리 생성
shm_id_1 = shmget((key_t)KYE_NUM_1,MEM_SIZE,IPC_CREAT|0666);
shm_id_2 = shmget((key_t)KYE_NUM_2,MEM_SIZE,IPC_CREAT|0666);
shm_id_3 = shmget((key_t)KYE_NUM_3,MEM_SIZE,IPC_CREAT|0666);
shm_id_4 = shmget((key_t)KYE_NUM_4,MEM_SIZE,IPC_CREAT|0666);
shm_id_5 = shmget((key_t)KYE_NUM_5,MEM_SIZE,IPC_CREAT|0666);


//공유메모리첨부
wait_1 = shmat(shm_id_1,0,0);
wait_2 = shmat(shm_id_2,0,0);
wait_3 = shmat(shm_id_3,0,0);
wait_4 = shmat(shm_id_4,0,0);
complete = shmat(shm_id_5,0,0);

init(wait_1);
init(wait_2);
init(wait_3);
init(wait_4);
init(complete);

wait_1->ok = 1;
wait_2->ok = 1;
wait_3->ok = 1;
wait_4->ok = 1;



Init_account(fp,wait_1, wait_2, wait_3, wait_4, int arr_account[]);


pid_t pid;



while(!is_empty(wait_1) || !is_empty(wait_2) /*|| !is_empty(wait_3) || !is_empty(wait_4)*/)
{

pid = fork();
if(pid == 0)
{

if(wait_1->ok == 1)
{
Deposit(wait_1, complete);
exit(0);
}

else if(wait_2->ok == 1)
{
WithDraw(wait_2,complete);
exit(0);
}

else
exit(0);

}


sleep(1);

}

WriteData(fp, complete);

return 0;


}
