#include <stdio.h>
#include <cuda_runtime.h>
#include <stdbool.h> 
#include <string.h>

//打印GPU信息
void printDeviceProp(const cudaDeviceProp &prop)
{
    printf("Device Name : %s.\n", prop.name);
    printf("totalGlobalMem : %ld.\n", prop.totalGlobalMem);
    printf("sharedMemPerBlock : %ld.\n", prop.sharedMemPerBlock);
    printf("regsPerBlock : %d.\n", prop.regsPerBlock);
    printf("warpSize : %d.\n", prop.warpSize);
    printf("memPitch : %ld.\n", prop.memPitch);
    printf("maxThreadsPerBlock : %d.\n", prop.maxThreadsPerBlock);
    printf("maxThreadsDim[0 - 2] : %d %d %d.\n", prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
    printf("maxGridSize[0 - 2] : %d %d %d.\n", prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
    printf("totalConstMem : %ld.\n", prop.totalConstMem);
    printf("major.minor : %d.%d.\n", prop.major, prop.minor);
    printf("clockRate : %d.\n", prop.clockRate);
    printf("textureAlignment : %ld.\n", prop.textureAlignment);
    printf("deviceOverlap : %d.\n", prop.deviceOverlap);
    printf("multiProcessorCount : %d.\n", prop.multiProcessorCount);
}


bool initCUDA()
{
    //used to count the device numbers
    int count;
 
    // get the cuda device count
    cudaGetDeviceCount(&count);
    printf("cuda device count: %d\n",count);
    if (count == 0) {
        fprintf(stderr, "There is no device.\n");
        return false;
    }
 
    // 寻找指定的Tesla GPU
    int i;
    for (i = 0; i < count; ++i) {
        cudaDeviceProp prop;
        if (cudaGetDeviceProperties(&prop, i) == cudaSuccess) {
            printf("Device Name : %s.\n", prop.name);
            if ( (strcasecmp(prop.name, "Tesla P40")) == 0) {
               printf("Device Name : %s.\n", prop.name);  //被选定的设备在打印时，应该被连续打印两次
               break;
            }
        }
    }
 
    // if can't find the device
    if (i == count) {
        fprintf(stderr, "There is no device supporting CUDA 1.x.\n");
        return false;
    }
    cudaSetDevice(i);
    return true;
}
 
int main(int argc, char const *argv[])
{
    if (initCUDA()) {
        printf("CUDA initialized.\n");
    }
 
    return 0;
}
