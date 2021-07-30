#include <stdio.h>
#include <cuda_runtime.h>

int main(){
  int driverVersion;
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start, 0);
  cudaDriverGetVersion(&driverVersion);//CUDA代码
  cudaEventRecord(stop,0);
  cudaEventSynchronize(stop);
  float elapsedTime;   //存放时间间隔
  cudaEventElapsedTime(&elapsedTime, start, stop);
  printf("The time elapsed time is %5.5f\n", elapsedTime);
  printf("CUDA Driver Version:%d.%d\n",driverVersion/1000,driverVersion/100);
  return 0;
}
