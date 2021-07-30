//nvcc -std=c++11 -o test -I/usr/local/cuda/samples/common/inc  _cudaHadamard.cu -lcuda
#include <newton/newton.hpp>

int main()
{
  float a[4] = {1.0, 1.0, 1.0, 1.0};
  float b[4] = {2.0, 2.0, 2.0, 2.0};
  float c[4] = {};

  newton::numeric_vector<float> A = a;
  newton::numeric_vector<float> B = b;
  newton::numeric_vector<float> C = c;
  for (int i = 0 ; i < 10000000; i++){
     C = A * B;
  }
  //C = A * B;
  thrust::copy(C.begin(), C.end(), std::ostream_iterator<float>(std::cout, " "));
  std::cout << std::endl;
  return 0;
}
