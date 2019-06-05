# tinycrc32
## Introduction
This is a small header only library that contains both hadware-accelerated and not hardware-accelerated implementations of the crc32c algorithm. Please note that the Castagnoli version of the CRC32 algorithm here uses the `0x1EDC6F41` polynomial and not the standard one i.e `0x04C11DB7`. For detailed documentation please refer to the pdfs in the `docs` directory and the source file itself.

## Quickstart
In the header file there is basically just one function one wants to call as depending on the compile flags a different implementation will be used for that function. For example the following `main.cpp` file
```cpp
#include <cstring>
#include <iostream>

#include "tinycrc32.h"

int main() {
  std::size_t n = 1031 
  uint8_t *data = new uint8_t[n];
  std::memset(data, 7, n);

  std::cout << crc32c(data, n) << std::endl;

  delete[] data;
  return 0;
}
```
can be compiled in three different ways. First the default version, which does not have any hardware acceleration enabled.  
```
g++ -std=c++11 ./main.cpp -o main
```  
The second version with SSE42 hardware acceleration can be compiled by adding the `-DENABLE_SSE42` compiler flag.  
```
g++ -std=c++11 -DENABLE_SSE42 -o main
```  
Laslty to enable the pipling of the CRC32 instruction using the `PCLMULQDQ` instructions the `-DENABLE_PCLMULQDQ` flag must be passed to the compiler.  
```
g++ -std=c++11 -DENABLE_SSE42 -DENABLE_PCLMULQDQ -o main
```  

## Testing & Benchmarking
The test and benchmark executable can be build by running `make test` and `make benchmark` respectively. It is important to note though that google-test is required for the test executable and google-benchmark for the benchmark executable. To enable hardware acceleration in the test and benchmark executable please check the makefile.
