/**
  * 首先该段互斥程序能够正确的执行，使用命令gcc -o test criticalSection2.c -lpthread将该段代码编译，生成可执行文件test，接着运行./loop脚本即可在output中看到结果。
  * 正确的步骤如下：
  * 0. 在头文件中包含#include <semaphore.h>，它没有被包含在pthread.h线程库中
  * 1. 申请全局的信号量sem_t mutex
  * 2. 在主线程（main函数）中初始化该信号量 sem_init(&mutex, 0, 1)，该函数第二个参数默认设置为0，第三个参数是信号量的初始值，设置为1，这样才能保证第一个线程能够进入临界区
  * 3. 在访问临界区使用前使用 sem_wait(&mutex)，判断当前信号量是否为0，如果信号量为0，则等待，如果信号量不为0， 则减1进入临界区
  * 4. 使用完信号量后释放 sem_post(&mutex); 信号量使用完后，使用sem_post将mutex的值加1，这样能够保证正在等待的线程被执行
  * 5. 在主线程（main函数）中销毁信号量 sem_destroy(&mutex)
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>  //1. 包含semaphore头文件
#define N 40

int sum = 0;   //全局变量，由不同的应用程序调用可能会产生竞争，被称为临界区，也称为互斥量
int sub = 40;
sem_t mutex;    //2. 设置semaphore全局变量 

void* add(void* tid){
  int id = (int)tid;
  //printf("进入到线程%d.\n", id);
  sem_wait(&mutex);   //4. 进入临界区前使用sem_wait函数，判断mutex，如果是0，则等待，如果非0，则对mutex减1后进去临界区
  sum += 1;    //临界区数据发生变化
  sub -= 1;
  sem_post(&mutex);  //5. 完成临界区的访问后，调用sem_post，对mutex信号量的值加1，使得等待的线程能够正常运行
  return NULL;
}

int main(){
  sem_init(&mutex,0, 1);  //3. 初始化semaphore全局变量，并且设定初始值为1
  pthread_t *pthread_handles;
  pthread_handles = malloc(N*sizeof(pthread_t));
  for (int i = 0 ; i < N; i++){
    pthread_create(&pthread_handles[i], NULL, add, (void*)i);
  }
  
  for (int i = 0 ; i < N; i++){
    pthread_join(pthread_handles[i],NULL);
  }

  free(pthread_handles);
  printf("sum = %d\n", sum);
  printf("sub = %d\n", sub);
  sem_destroy(&mutex);  //6. 释放信号量mutex
  return 0;
}
