#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#define size 5

char shared_space[size];
char c;
int i=0,j=0,memory_index=0;
void *producer(void *);
void *consumer(void *);

sem_t prod;
sem_t cons;

int main()
{
    int no_prod,no_cons;
    printf("Enter No Of Producer : ");
    scanf("%d",&no_prod);
    printf("Enter No Of Consumer : ");
    scanf("%d",&no_cons);

    pthread_t prod_thread[no_prod];
    pthread_t cons_thread[no_cons];

    sem_init(&prod, 0, no_prod);
    sem_init(&cons, 0, 0);
    int choice ;
    int flag=1;
   while(flag)
   {
        printf("1-Produce \n");
        printf("2-Consume \n");
        printf("3-List \n");
        printf("4-Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1 :
         pthread_create(&prod_thread[i], NULL, producer , (void *)&i);
         pthread_join(prod_thread[i],NULL);
         i++;
         break;
        case 2 :
          pthread_create(&cons_thread[j], NULL,consumer , (void *)&j);
          pthread_join(cons_thread[j],NULL);
          j++;
          break;
        case 3:
          if(index==0)
          printf("Memory Is Empty \n");
          else
          {
          for(int k=0 ; k<memory_index ; k++)
          printf("%c\n",shared_space[k]);
          }
          break;
        case 4 :
          flag=0;
          break;
        default :
           printf("Entered Wrong choice ");
        }
       
      
    }

 

    sem_destroy(&prod);
    sem_destroy(&cons);

    return 0;
}

void *producer(void *prod_no)
{
    int x = *((int*)prod_no);
    sem_wait(&prod);
    printf("What You Want To Produce? \n");
    scanf(" %c",&c);                                                 
    shared_space[memory_index]=c;
    printf("Producer No %d Start Producing \n" , x );
    printf("Producer No %d Produced %c \n",x,c);
    memory_index++;
    sem_post(&cons);
}

void *consumer(void *consumer_no)
{
    int x = *((int*)consumer_no);
    sem_wait(&cons);
    printf("What You Want To Consume ?\n ");
    scanf(" %c",&c);                                                    
     printf("Consumer No %d Start Consuming \n" ,x );
     int check=0;
    for(int k=0; k<i ; k++)
    {
    if(c==shared_space[k])
    {
    for(int l=k; l<i-1 ; l++)
    {
    shared_space[l]=shared_space[l+1];
    }
    check=1;
    }
    }
   if(check)
   {
    printf("Consumer No %d has Consumed %c \n",x,c);
    sem_post(&prod);
    memory_index--;
   }
   else
   printf("Cant Consume ! Not In Memory \n");
}



