#pragma once

#ifndef __BANK_H__

#define __BANK_H__

 


#include<stdio.h>

#include<stdlib.h>

#include<math.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<fcntl.h>

 

#define TRUE 1

#define FALSE 0

#define MAX_QUEUE_SIZE 100

#define MAX_LEN 20

 

 
typedef struct

{

   int number;

   int account;

   char name[MAX_LEN];

   int bankmoney;

   int money;


}element;

 

typedef struct

{
int ok;

element queue[MAX_QUEUE_SIZE];

int front, rear;

}QueueType;

 

//Queue function

void error(char *message);

void init(QueueType *q);

int is_empty(QueueType *q);

int is_full(QueueType *q);

void enqueue(QueueType *q, element item);

element dequeue(QueueType *q);
  
element peek(QueueType *q);


//Function
void Init_account(FILE *fp, QueueType *wait_1, QueueType *wait_2, QueueType *wait_3, QueueType *wait_4); 

void Deposit(QueueType *q, QueueType *complete);

void WithDraw(QueueType *q, QueueType *complete);

void WriteData(FILE *fp, QueueType *complete);

 



 

#endif
