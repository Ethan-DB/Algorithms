#include <stdio.h>
#include <cuda.h>

// Kernel that executes on the CUDA device
__global__ void square_array(float *a, int N)
{
#define STRIDE       32
#define OFFSET        0
#define GROUP_SIZE  512
  int n_elem_per_thread = N / (gridDim.x * blockDim.x);
  int block_start_idx = n_elem_per_thread * blockIdx.x * blockDim.x;
  int thread_start_idx = block_start_idx
            + (threadIdx.x / STRIDE) * n_elem_per_thread * STRIDE
            + ((threadIdx.x + OFFSET) % STRIDE);
  int thread_end_idx = thread_start_idx + n_elem_per_thread * STRIDE;
  if(thread_end_idx > N) thread_end_idx = N;
  int group = (threadIdx.x / GROUP_SIZE) & 1;
  for(int idx=thread_start_idx; idx < thread_end_idx; idx+=STRIDE)
  {
    if(!group) a[idx] = a[idx] * a[idx];
    else       a[idx] = a[idx] + a[idx];
  }
}
// main routine that executes on the host
int main(void)
{
  float *a_h, *a_d;  // Pointer to host & device arrays
  const int N = 1<<25;  // Make a big array with 2**N elements
  size_t size = N * sizeof(float);
  a_h = (float *)malloc(size);        // Allocate array on host
  cudaMalloc((void **) &a_d, size);   // Allocate array on device
  // Initialize host array and copy it to CUDA device
  for (int i=0; i<N; i++) a_h[i] = (float)i;
  cudaMemcpy(a_d, a_h, size, cudaMemcpyHostToDevice);
  
  // Set number of threads and blocks
  int n_threads_per_block = 1<<9;  // 512 threads per block
  int n_blocks = 1<<10;  // 1024 blocks
  // Do calculation on device
  square_array <<< n_blocks, n_threads_per_block >>> (a_d, N);
  cudaThreadSynchronize();  // Wait for square_array to finish on CUDA
  // Retrieve result from device and store it in host array
  cudaMemcpy(a_h, a_d, sizeof(float)*N, cudaMemcpyDeviceToHost);
  // Print some of the results and the CUDA execution time
  for (int i=0; i<N; i+=N/50) printf("%d %f\n", i, a_h[i]);
  // Cleanup
  free(a_h); cudaFree(a_d);
}

