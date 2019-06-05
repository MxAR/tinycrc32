SHELL=/bin/sh
CC=g++
CXXFLAGS= -std=c++11

# if the current architecture support the SSE42 extension it makes
# sense to uncomment the line below as an performance improvement
# can be achieved

# CXXFLAGS += -march=native -DENABLE_SSE42

# further if the PCLMULQDQ instruction are supported the crc32
# instructions can be pipelined for even greater efficency; ergo
# uncommenting the line below as well is advised

# CXXFLAGS += -DENABLE_PCLMULQDQ

# comment out CXXFLAGS line below to disable optimizations
CXXFLAGS += -O3 -DNDEBUG -fomit-frame-pointer -fstrict-aliasing -ffast-math

# comment out CXXFLAGS line below to disable warnings
CXXFLAGS += -Wall -Wextra

all: test benchmark

clean:
	rm -f benchmark test *.out

test:
	$(CC) $(CXXFLAGS) test.cpp -lgtest -o test

benchmark:
	$(CC) $(CXXFLAGS) bench.cpp -lbenchmark -o benchmark
