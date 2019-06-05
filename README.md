# tinycrc32
## Introduction
This is a small header only library that contains both hadware-accelerated and not hardware-accelerated implementations of the crc32c algorithm. Please note that the Castagnoli version of the CRC32 algorithm here uses the `0x1EDC6F41` polynomial and not the standard one i.e `0x04C11DB7`. For detailed documentation please refer to the pdfs in the `docs` directory and the source file itself.

## Quickstart
In the header file there is basically just one function one wants to call as depending on the compile flags different algorithms will be used. For example the following `main.cpp` file
```cpp
#include <cstring>
#include <iostream>

#include "tinycrc32.h"

int main() {
  uint8_t *data = new uint8_t[10];
  std::memset(data, 7, 10);

  std::cout << crc32c(data, 10) << std::endl;

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

### Testing
The test can be build by running `make test` assuming that google-test is installed.  

### Benchmarking
The benchmark can be build via running `make benchmark` assuming that google-benchmark is installed.

### Hardware Support
As previously mentioned this library contains hardware-accelerated versions of the CRC32C algorithm. Acceleration is facilitated via the `_mm_crc32_u64` instruction form the SSE42 extension. Pipelining is also supported through carry-less multiplication which uses the `PCLMULQDQ` instructions. To enable those accelerations please refer to the make file.
