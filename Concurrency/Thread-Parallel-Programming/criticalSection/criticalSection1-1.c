/**
  * @author Junpen Zhu
  * 代码实现功能：假设A现在有1500元(sum1)，B现在有500元(sum2)，紧接着A将调用add代码，给B转钱，每次转走200元，相应的自己就减少200元，钱可以为负值
  * 上述过程持续N次，等待结束完成之后，B会调用sub函数，再给自己加300元
  * 该问题在criticalSection1.c中提出，主要涉及的问题是线程add和线程sub可能会同时写同一块共享内存（即全局变量），因此一个线程在写时，另外一个线程只能读，两者不能同时执行写操作
  * 本程序采用读写锁解决线程之间的同步问题。
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 40

int sum1 = 1500;
int sum2 = 500;

pthread_rwlock_t rwlock;    //1. 创建全局读写锁，全局公共变量使得所有的线程都能够共同访问该变量


void* add(void* tid){
  //int id = (int)tid;
  //printf("进入到线程%d.\n", id);
  pthread_rwlock_wrlock(&rwlock); //3. 在访问临界区时加写锁
  sum2 = sum1 - 200;    //临界区数据发生变化
  sum1 = sum1 - 200;
  pthread_rwlock_unlock(&rwlock);   //4. 处理完临界区以后，释放写锁
  return NULL;
}

void* sub(void* tid){
  //int id = (int)tid;
  //printf("进入到线程%d.\n", id);
  pthread_rwlock_wrlock(&rwlock); //3. 在访问临界区时加锁
  sum2 += 300;
  pthread_rwlock_unlock(&rwlock);   //4. 处理完临界区以后，释放锁
  return NULL;
}

int main(){
  pthread_rwlock_init(&rwlock, NULL); //2. 在主线程中初始化rwlock变量，第二个参数恒定为NULL
  
  pthread_t* sumPthread;
  sumPthread = malloc(N*sizeof(pthread_t));
  pthread_t* subPthread;
  subPthread = malloc(N*sizeof(pthread_t));
  
  for (int i = 0; i < N; i++){
    //pthread_rwlock_wrlock(&rwlock); //3. 在访问临界区时加锁
    pthread_create(&sumPthread[i], NULL, add, (void*)i);
    pthread_create(&subPthread[i], NULL, sub, (void*)i);
    //pthread_rwlock_wrlock(&rwlock);
  }
  //for (int i = 0; i < N; i++){
    //pthread_rwlock_wrlock(&rwlock); //3. 在访问临界区时加锁
    //pthread_create(&subPthread[i], NULL, sub, (void*)i);
    //pthread_rwlock_wrlock(&rwlock);
  //}

  for (int j = 0; j < N; j++){
    pthread_join(sumPthread[j],NULL);
    pthread_join(subPthread[j],NULL);
  }
  //for (int j = 0; j < N; j++){
    //pthread_join(subPthread[j],NULL);
  //} 
 
  printf("sum1 = %d\n", sum1);
  printf("sum2 = %d\n", sum2);
  pthread_rwlock_destroy(&rwlock);  //5. 释放掉rwlock变量，必须要完成以上五步，否则不会得到正确的计算结果
  return 0;
}
