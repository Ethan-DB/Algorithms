//nvcc -o test -I/usr/local/cuda/include -L/usr/local/cuda/lib64 _cudaDotProducts.cu -lcuda -lcublas
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include <stdio.h>

int main(void)
{
    const int nvals = 10;
    const size_t sz = sizeof(double) * (size_t)nvals;
    double x[nvals], y[nvals];
    double *x_, *y_, *result_;
    double result=0., resulth=0.;

    for(int i=0; i<nvals; i++) {
        x[i] = y[i] = (double)(i)/(double)(nvals);
        resulth += x[i] * y[i];
    }

    cublasHandle_t h;
    cublasCreate(&h);
    cublasSetPointerMode(h, CUBLAS_POINTER_MODE_DEVICE);

    cudaMalloc( (void **)(&x_), sz);
    cudaMalloc( (void **)(&y_), sz);
    cudaMalloc( (void **)(&result_), sizeof(double) );

    cudaMemcpy(x_, x, sz, cudaMemcpyHostToDevice);
    cudaMemcpy(y_, y, sz, cudaMemcpyHostToDevice);

    cublasDdot(h, nvals, x_, 1, y_, 1, result_);

    cudaMemcpy(&result, result_, sizeof(double), cudaMemcpyDeviceToHost);

    printf("%f %f\n", resulth, result);

    return 0;
}
