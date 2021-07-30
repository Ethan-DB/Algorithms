#include <stdio.h>
#include <cuda_runtime.h>

int main(){
  int driverVersion;
  cudaDriverGetVersion(&driverVersion);
  printf("CUDA Driver Version:%d.%d\n",driverVersion/1000,driverVersion/100);
  return 0;
}
