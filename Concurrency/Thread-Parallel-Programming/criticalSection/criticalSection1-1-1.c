/**
  * @author Junpen Zhu
  * 代码实现功能：假设A现在有1500元(sum1)，B现在有500元(sum2)，紧接着A将调用add代码，给B转钱，每次转走200元，相应的自己就减少200元，钱可以为负值
  * 上述过程持续N次，等待结束完成之后，B会调用sub函数，再给自己加300元
  * 该问题在criticalSection1.c中提出，主要涉及的问题是线程add和线程sub可能会同时写同一块共享内存（即全局变量），因此一个线程在写时，另外一个线程只能读，两者不能同时执行写操作
  * 本程序增加一个counter变量来实现不同线程之间的同步，当counter达到add的最大线程数时，激活sub函数
  * 这种思路的本质是：采用一个只有add函数会修改的全局变量来控制不同函数产生的线程的执行顺序
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N 40

int sum1 = 1500;
int sum2 = 500;
int counter = 0;  //表示当前add线程的个数

sem_t mutex_add;   //1. 申请全局信号量，该信号量用于控制add的执行
sem_t mutex_sub;

void* add(void* tid){
  //int id = (int)tid;
  //printf("进入到线程%d.\n", id);
  sem_wait(&mutex_add); //3. 在访问临界区时加锁
  counter++;
  sum2 = sum1 - 200;    //临界区数据发生变化
  sum1 = sum1 - 200;
  if(counter == N-1){  // 线程从0开始编号直到39，当counter为39时，解锁sub函数的所有线程
    sem_post(&mutex_sub);
  }
  sem_post(&mutex_add);   //4. 处理完临界区以后，释放锁
  return NULL;
}

void* sub(void* tid){
  //int id = (int)tid;
  //printf("进入到线程%d.\n", id);
  sem_wait(&mutex_sub); //3. 在访问临界区时加锁
  sum2 += 300;
  sem_post(&mutex_sub);   //4. 处理完临界区以后，释放锁
  return NULL;

}

int main(){
  sem_init(&mutex_add, 0, 1); //2. 在主线程中初始化mutex变量，第二个参数恒定为NULL
  sem_init(&mutex_sub, 0 ,0);  //  将控制sub函数执行的信号量初始化为0，先完成所有的加法运算
  pthread_t* sumPthread;
  pthread_t* subPthread;
  sumPthread = malloc(N*sizeof(pthread_t));
  subPthread = malloc(N*sizeof(pthread_t));
  for (int i = 0; i < N; i++){
    pthread_create(&sumPthread[i], NULL, add, (void*)i);
  }  //创建40个sum线程
  
  for (int i = 0 ; i < N; i++){
    pthread_create(&subPthread[i], NULL, sub, (void*)i);
  }  //创建40个sub线程
  for (int j = 0; j < N; j++){
    pthread_join(sumPthread[j],NULL);
  }
  for (int j = 0; j < N; j++){
    pthread_join(subPthread[j],NULL);
  }
   
  printf("sum1 = %d\n", sum1);
  printf("sum2 = %d\n", sum2);
  sem_destroy(&mutex_add);  //5. 释放掉mutex变量，必须要完成以上五步，否则不会得到正确的计算结果
  sem_destroy(&mutex_sub);
  return 0;
}
