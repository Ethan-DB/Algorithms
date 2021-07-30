//gcc -o test addTwoThread.c -L. -lthpool -lpthread
#include "thpool.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define N 666666
//#define N 100
//#define N 20
int c[N]; //法则一：线程之间的共享变量应该是全部变量。要注意共享变量的相同部分是否可能被不同线程同时操作，如果是这样，涉及共享变量的部分应该用pthread_mutex_t结构“锁”起来
/**
  * 多线程要传送的参数，必须要封装起来，在传递时将其封装成void* 类型
*/
struct arguments{
  int start;
  int* a;
  int* b;
  int num;
};

//线程
void add(void* args){
  struct arguments *args_thread = (struct arguments*)args;
  int tid = args_thread->start;
  //printf("进入线程%d.\n",tid);
  while (tid < (args_thread->num)){
    //printf("进入线程执行%d of %d.\n", tid, args_thread->start);
    c[tid] = (args_thread->a)[tid] + (args_thread->b)[tid];
    tid += 2;
  }
}


int main(int argc, char* argv[]){
  if(argc != 2){ 
    fprintf(stderr, "The usage of is exefile <thread_number>\n");
    return 0;
  }
  int a[N]; 
  int b[N];
  for (int i = 0 ; i < N; i++){
    a[i] = -1*i;
    b[i] = i + i;
  }
  struct arguments arg1, arg2;
  arg1.a = a;
  arg1.b = b;
  arg1.start = 0;
  arg1.num = N;
  
  arg2.a = a;
  arg2.b = b;
  arg2.start = 1;
  arg2.num = N;
  //printf("%s\n",argv[1]); 
  threadpool thpool = thpool_init(atoi(argv[1]));  //argv[1]指定线程的个数
  //threadpool thpool = thpool_init(2);
  clock_t start = clock();
  //printf("The number of thread: %d.\n",thpool_num_threads_working(thpool));
  thpool_add_work(thpool, (void*)add, (void*)&arg1);
  thpool_add_work(thpool, (void*)add, (void*)&arg2);
  thpool_wait(thpool);
  clock_t end = clock() - start;
  //printf("The number of thread: %d.\n",thpool_num_threads_working(thpool)); 
  thpool_destroy(thpool);
  int i = 0 ;
  while (i < N){
    //printf("%d\n",c[i]);
    i += 1;
  }  //多线程打印出结果 
  //clock_t end = clock() - start;
  printf("The multi CPU is: %ld.\n",end);
  
  start = clock();
  for (int i = 0 ; i < N; i++){
    c[i] = a[i] + b[i];
  }  //单线程计算两个数组之和的时间
  end = clock() -start;
  for (int i = 0 ; i < N; i++){
    //printf("%d\n",c[i]);
  }   //单线程打印出结果

  printf("The single CPU is: %ld.\n",end);

  return 0;
}
