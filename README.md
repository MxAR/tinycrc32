# tinycrc32
## Introduction
This is small header only library (256 lines) that contains hadware-accelerated and not hardware-accelerated version of the crc32c algorithm. Please note that the Castagnoli version of the CRC32 algorithm here uses the `0x1EDC6F41` polynomial and not the standard one i.e `0x04C11DB7`.

## Testing
The test can be build by simple running `make test` and the executing the resulting executable.

## Benchmarking
Just as with the test the benchmark executable can be build via running `make benchmark` and executing that executable.

## Hardware Support
As previously mentioned this library also contains hardware-accelerated versions of the CRC32C algorithm. Acceleration is facilitated mainly via the `_mm_crc32_u64` instruction form the SSE42 extension. Pipelining is also supported via carry-less multiplication which uses the `PCLMULQDQ` instructions. To enable those accelerations please refer to the make file.
