//gcc -o test addThreeThread.c -L. -lthpool -lpthread
#include "thpool.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define N 666666
int c[N];    //全局数组
/**
  * 多线程要传送的参数，必须要封装起来，在传递时将其封装成void* 类型
*/
struct arguments{
  int start;
  int* a;
  int* b;
  int num;
};

//线程1
void add1(void* args){
  struct arguments *args_thread = (struct arguments*)args;
  int tid = args_thread->start;
  while (tid < (args_thread->num)){
    c[tid] = (args_thread->a)[tid] + (args_thread->b)[tid];
    tid += 3;
  }
}

//线程2
void add2(void* args){
  struct arguments *args_thread = (struct arguments*)args;
  int tid = args_thread->start;
  while (tid < (args_thread->num)){
    c[tid] = (args_thread->a)[tid] + (args_thread->b)[tid];
    tid += 3;
  }
}

//线程3
void add3(void* args){
  struct arguments *args_thread = (struct arguments*)args;
  int tid = args_thread->start;
  while (tid < (args_thread->num)){
    c[tid] = (args_thread->a)[tid] + (args_thread->b)[tid];
    tid += 3;
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
  struct arguments arg1, arg2, arg3;  //分别指示三个线程的参数
  arg1.a = a;
  arg1.b = b;
  arg1.start = 0;
  arg1.num = N;
  
  arg2.a = a;
  arg2.b = b;
  arg2.start = 1;
  arg2.num = N;
  
  arg3.a = a;
  arg3.b = b;
  arg3.start = 2;
  arg3.num = N;
  //printf("%s\n",argv[1]); 
  threadpool thpool = thpool_init(atoi(argv[1]));  //argv[1]指定线程的个数
  clock_t start = clock();
  thpool_add_work(thpool, (void*)add1, (void*)&arg1);
  thpool_add_work(thpool, (void*)add2, (void*)&arg2);
  thpool_add_work(thpool, (void*)add3, (void*)&arg3);
  thpool_wait(thpool);
  //printf("The number of thread: %d.\n",thpool_num_threads_working(thpool)); 
  thpool_destroy(thpool);
  //for (int i = 0 ; i < N; i++){
    //printf("%d\t",c[i]);
  //}
  clock_t end = clock() - start;
  printf("The multi CPU is: %ld.\n",end);
  
  start = clock();
  for (int i = 0 ; i < N; i++){
    c[i] = a[i] + b[i];
    //printf("%d\t",c[i]);
  }
  end = clock() -start;
  printf("The single CPU is: %ld.\n",end);

  return 0;
}
