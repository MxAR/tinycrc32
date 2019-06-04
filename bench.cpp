#include <benchmark/benchmark.h>
#include <cstring>

#include "tinycrc32.h"

static void bench_crc32c(benchmark::State &state) {
  std::size_t n = state.range(0);
  uint8_t *data = new uint8_t[n];
  std::memset(data, (n - 1) % 256, n);

  uint32_t crc;
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(crc = crc32c(data, n));
  }

  delete[] data;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(bench_crc32c)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 12)
    ->Complexity(benchmark::oN);
BENCHMARK_MAIN();
