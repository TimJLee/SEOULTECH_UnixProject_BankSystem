#include"bank.h"

 
QueueType queue;



 

 

void error(char *message)

{

   fprintf(stderr, "%s\n", message);

}

 

 

void init(QueueType *q)

{

   q->front = q->rear = 0;

}

 

int is_empty(QueueType *q)

{

   return (q->front == q->rear);

}

 

int is_full(QueueType *q)

{

   return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);

}

 

 

void enqueue(QueueType *q, element item)

{

   if (is_full(q))

   {

      char mesg[] = "Queue is full";

      error(mesg);

   }

 

   q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;

   q->queue[q->rear] = item;

 

}


element dequeue(QueueType *q)

{

   if (is_empty(q))

   {
      char mesg[] = "Queue is full";
      error(mesg);
   }

   q->front = (q->front + 1) % MAX_QUEUE_SIZE;
   return q->queue[q->front];

}

 

 

element peek(QueueType *q)

{

 

   if (is_empty(q))

   {

      char mesg[] = "Queue is empty";
      error(mesg);

   }

 

   return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];

 

}


void Init_account(FILE *fp, QueueType *wait_1, QueueType *wait_2, QueueType *wait_3, QueueType *wait_4, int arr_account[])
{
element temp;
int i=0;

while(0 < fscanf(fp, "%d %d %s %d %d", &temp.number, &temp.account, temp.name, &temp.bankmoney, &temp.money))
{

//temp.account = arr_account[i++];
    arr_account[i++]=temp.account;
    
if(temp.number == 1)
enqueue(wait_1, temp);

else if(temp.number ==2)
enqueue(wait_2, temp);

else if(temp.number ==3)
enqueue(wait_3, temp);

else if(temp.number ==4)
enqueue(wait_4,temp);

}



}


void Deposit(QueueType *q, QueueType *complete)
{

    q->ok = 0;


    sleep(5);
    element temp = dequeue(q);
    temp.bankmoney += temp.money;
    temp.money = 0;
    enqueue(complete, temp);

    q->ok = 1;
    ////////출력
    printf("name : %s Deposit complete\n",temp.name);
    if((q->front-q->rear)>0)
        printf("%d customer is left",q->front-q->rear);
    if((q->front-q->rear)<0)
        printf("%d customer is left",(q->front-q->rear)*-1);

}




void WithDraw(QueueType *q, QueueType *complete)
{

q->ok = 0;


sleep(4);
element temp = dequeue(q);
if((temp.bankmoney-temp.money)>0)
temp.bankmoney -= temp.money;

enqueue(complete, temp);

q->ok= 1;


printf("name : %s WithDraw complete\n",temp.name);
if((q->front-q->rear)>0)
    printf("%d customer is left",q->front-q->rear);
if((q->front-q->rear)<0)
    printf("%d customer is left",(q->front-q->rear)*-1);
}

//3
void MakeAccount(QueueType *q, QueueType *complete, int arr_account[])
{
//Todo
    q->ok = 0;
    srand(time(NULL));
    int randNum=rand()*10%3+2;
    sleep(randNum);
    element temp = dequeue(q);


    while(1)
    {
        int rand_account=rand()*100000+10000;
        if(arr_account[i]!=rand_account){
            temp.account = random;
            enqueue(complete, temp);
            q->ok= 1;
            printf("name : %s MakeAccount complete\n",temp.name);
            if((q->front-q->rear)>0)
                printf("%d customer is left",q->front-q->rear);
            if((q->front-q->rear)<0)
                printf("%d customer is left",(q->front-q->rear)*-1);
            break;
        }
    }
}



void WriteData(FILE *fp, QueueType *complete)
{
rewind(fp);


while(!is_empty(complete))
{
element temp = dequeue(complete);
fprintf(fp,"%d %d %s %d %d\n",temp.number, temp.account, temp.name, temp.bankmoney, temp.money);
}


printf("Complete\n");

}









