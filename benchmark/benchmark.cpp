//
// Created by olivier on 28/11/18.
//

#include <benchmark/benchmark.h>
#include "../src/RC4.h"

static void oneplusone(benchmark::State& state) {
    for (auto _ : state) {
        1+1;
    }
}

BENCHMARK(oneplusone);

BENCHMARK_MAIN();