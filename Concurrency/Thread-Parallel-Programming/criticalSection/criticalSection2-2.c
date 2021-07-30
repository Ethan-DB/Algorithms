/**
  * 首先该段互斥程序能够正确的执行，使用命令gcc -o test criticalSection2.c -lpthread将该段代码编译，生成可执行文件test，接着运行./loop脚本即可在output中看到结果。
  * 本段程序使用循环忙等待代替互斥量，循环忙等待和互斥量的区别是：前者保证了线程等待和后续继续执行的顺序，但是互斥量是随机的，由系统决定
  * 正确的步骤如下：
  * 1. 申请全局的循环标志变量,unsigned int flag
  * 2. 在主线程（main函数）中初始化该循环标志量，flag = 0 
  * 3. 在临界区代码使用前进行判断  while(flag != tid)  判断flag是否等于tid，也就是线程编号
  * 4. 使用完循环标志量后应该允许下一个线程进入到临界区访问 flag = (flag+1)%thread_count
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 40

int sum = 0;   //全局变量，由不同的应用程序调用可能会产生竞争，被称为临界区，也称为互斥量
int sub = 40;
unsigned int flag;    //1. 申请循环标志量

void* add(void* tid){
  int id = (int)tid;
  //printf("进入到线程%d.\n", id);
  while (flag != id); //3. 在访问临界区时循环判断之前线程是否已经完成临界区的访问
  sum += 1;    //临界区数据发生变化
  sub -= 1;
  flag = (flag+1) % N;   //4. 给下一个线程访问临界区的权限
  return NULL;
}

int main(){
  flag = 0; //2. 初始化mutex变量，第二个参数恒定为NULL
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
  return 0;
}
