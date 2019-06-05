# tinycrc32
## Introduction
This is a small header only library (256 lines) that contains both hadware-accelerated and not hardware-accelerated implementations of the crc32c algorithm. Please note that the Castagnoli version of the CRC32 algorithm here uses the `0x1EDC6F41` polynomial and not the standard one i.e `0x04C11DB7`. For detailed documentation please refer to the pdfs in the `docs` directory and the source file itself.

## Testing
The test can be build by running `make test` assuming that google-test is installed.  

## Benchmarking
The benchmark can be build via running `make benchmark` assuming that google-benchmark is installed.

## Hardware Support
As previously mentioned this library contains hardware-accelerated versions of the CRC32C algorithm. Acceleration is facilitated via the `_mm_crc32_u64` instruction form the SSE42 extension. Pipelining is also supported through carry-less multiplication which uses the `PCLMULQDQ` instructions. To enable those accelerations please refer to the make file.
