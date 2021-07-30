#include <stdio.h>
#include <cuda.h>
#include <cuComplex.h>

int main(){
  cuInit(0);
  double cr = 1;
  double ci = 2;
  double r = 3;
  cuDoubleComplex c = make_cuDoubleComplex(cr, ci);
  cuDoubleComplex result = cuCmul(c, make_cuDoubleComplex(r, 0));
  printf("%f + i%f\n", cuCreal(result), cuCimag(result));
  return 0;
}

