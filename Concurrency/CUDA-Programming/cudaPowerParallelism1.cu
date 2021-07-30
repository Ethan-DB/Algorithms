#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#define DATA_SIZE 1048576     //该数值随便指定
#define THREAD_NUM 256
int data[DATA_SIZE];    //全局data数组，要计算数组中数据的平方和

/*
  * @author Junpeng Zhu
  * @功能  为当前程序设置一个合适的GPU，当然还有其它的方式能够实现该功能，比如设置环境变量
*/
bool InitCUDA(){
  int count;
  cudaGetDeviceCount(&count);   //统计计算机中支持CUDA的显卡的个数
  if (count == 0){
    fprintf(stderr, "There is no device!\n");
    return false;
  }
  
  int i;
  for (i = 0; i < count; i++){
    cudaDeviceProp prop;
    if (cudaGetDeviceProperties(&prop,i) == cudaSuccess){
      if (prop.major >= 1 and prop.minor >= 0){
        break;
      }
    }
  }
  if (i == count){
    fprintf(stderr,"There is no device support CUDA 1.x.\n");
    return false;
  }

  cudaSetDevice(i);   //设定满足>=1.0的计算设备为当前程序需要的计算设备
  return true;
}

/*
  * @author Junpeng Zhu
  * @功能  随机数生成函数，生成0-9的以内的整数
*/
void GenerateNumbers(int *number, int size){
  srand((unsigned)time(NULL));
  for (int i =0; i < size; i++){
    number[i] = rand() % 10;
  }
}

/*
 * kernel function is performced in the GPU device.
 * @author Junpeng Zhu
*/
__global__ static void sumOfSquares(int* num, int* result, clock_t* time){
  const int tid = threadIdx.x;    //threadIdx是CUDA的内建变量，表示当前的thread是第几个thread（从0开始计算）
  const int size = DATA_SIZE / THREAD_NUM;
  int sum = 0;
  int i;
  clock_t start;
  if (tid == 0) start = clock();
  for (i = tid*size; i < (tid+1)*size; i++){
    sum += num[i] * num[i];
  }

  result[tid] = sum;
  if (tid == 0) *time = clock()-start;
}


int main(){
  if (!InitCUDA()){
    return 0;
  }else{
    printf("CUDA initialized.\n");
    GenerateNumbers(data, DATA_SIZE);   //生成指定规模的随机数据，所有数据范围均在0-9
    int *gpudata, *result;
    clock_t* time;
    if (!(cudaMalloc((void**) &gpudata, sizeof(int) * DATA_SIZE) == cudaSuccess)){
      fprintf(stderr, "Memory error.\n");
      return 0;
    }//在device上分配一块linear地址空间，地址为&gpudata，每个单元大小为int，总共DATA_SIZE个单元
    if(!(cudaMalloc((void **) &result, sizeof(int)* THREAD_NUM)==cudaSuccess)){
      fprintf(stderr, "Memory error.\n");
      return 0;
    }  //在device上分配内存，大小为int
    if(!(cudaMalloc((void**) &time, sizeof(clock_t)) == cudaSuccess)){
      fprintf(stderr, "Memory error.\n");
      return 0;
    }
    if(!(cudaMemcpy(gpudata, data, sizeof(int) * DATA_SIZE, cudaMemcpyHostToDevice)== cudaSuccess)){
      fprintf(stderr, "Memory error.\n");
      return 0;
    }  //从host的data中将DATA_SIZE个单元的数据复制到device的gpudata中，这是输入数据，需要从host中获取
    
    sumOfSquares<<<1,THREAD_NUM,0>>>(gpudata,result,time);
    int sum_gpu[THREAD_NUM];  // 将GPU计算结果拷贝到该变量中
    clock_t used_time;
    cudaMemcpy(&sum_gpu, result, sizeof(int)*THREAD_NUM, cudaMemcpyDeviceToHost);   //将GPU中的result值拷贝到CPU的sum变量中
    cudaMemcpy(&used_time, time, sizeof(clock_t), cudaMemcpyDeviceToHost);
    
    int final_sum = 0;
    for (int i = 0; i < THREAD_NUM; i++){
      final_sum += sum_gpu[i];
    }
    printf("The GPU sum is %d.\n", final_sum);
    cudaFree(gpudata);
    cudaFree(result);
    cudaFree(time);
    printf("The GPU time is %ld.\n",used_time);
    int j;
    int sum_cpu = 0;
    clock_t start = clock();
    for (j=0; j < DATA_SIZE; j++){
      sum_cpu += data[j] * data[j];
    }
    clock_t end = clock()-start;
    printf("The CPU sum is %d.\n", sum_cpu);
    printf("The CPU time is %ld.\n",end);
    return 0;
  }
}
