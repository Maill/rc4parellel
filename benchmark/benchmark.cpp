/**
 * Benchmark methods
 * benchmark.cpp
 * Purpose : Getting timing performance of the core program
 *
 * @authors Nicolas Cornu, Olivier Lefebvre, Vincent Valvas
 * @version 0.1
 * @date 28/11/18
 */

#include <benchmark/benchmark.h>
#include "../src/Common/Functions.h"
#include "../src/FileAccessor/FileAccessor.h"
#include "../src/ThreadManager/ThreadManager.h"

//How many threads to use on parallel benchmarks
const int nbThread = 4;

//////////////////////////////////////////////////////////////
static void encryptTinyTextFileOneThread(benchmark::State& state) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/1_input";
    string pathOutput = "../data/2_input";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, 1, key);
        tm.startWork();
    }
}

static void decryptTinyTextFileOneThread(benchmark::State& state) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/2_input";
    string pathOutput = "../data/2_output";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, 1, key);
        tm.startWork();
    }
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
static void encryptTinyTextFileParallel(benchmark::State& state) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/1_input";
    string pathOutput = "../data/2_input";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, nbThread, key);
        tm.startWork();
    }
}

static void decryptTinyTextFileParallel(benchmark::State& state) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/2_input";
    string pathOutput = "../data/2_output";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, nbThread, key);
        tm.startWork();
    }
}
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
static void encryptBigTextFileOneThread(benchmark::State& state) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/3_input";
    string pathOutput = "../data/4_input";
    
    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, 1, key);
        tm.startWork();
    }
}

static void decryptBigTextFileOneThread(benchmark::State& state) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/4_input";
    string pathOutput = "../data/4_output";
    
    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, 1, key);
        tm.startWork();
    }
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
static void encryptBigTextFileParallel(benchmark::State& state) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/3_input";
    string pathOutput = "../data/4_input";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, nbThread, key);
        tm.startWork();
    }
}

static void decryptBigTextFileParallel(benchmark::State& state) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/4_input";
    string pathOutput = "../data/4_output";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, nbThread, key);
        tm.startWork();
    }
}
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
static void encryptBigBinaryFileOneThread(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/5_input.jpg";
    string pathOutput = "../data/6_input";
    
    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, 1, key);
        tm.startWork();
    }
}

static void decryptBigBinaryFileOneThread(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/6_input";
    string pathOutput = "../data/6_output.jpg";
    
    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, 1, key);
        tm.startWork();
    }
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
static void encryptBigBinaryFileParallel(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/5_input.jpg";
    string pathOutput = "../data/6_input";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, nbThread, key);
        tm.startWork();
    }
}

static void decryptBigBinaryFileParallel(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/6_input";
    string pathOutput = "../data/6_output.jpg";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, nbThread, key);
        tm.startWork();
    }
}
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
static void encrypt1GoBinaryFileParallel(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigzipfile";
    string pathInput = "../data/1GB.zip";
    string pathOutput = "../data/1GB.zip.rc4";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, nbThread, key);
        tm.startWork();
    }
}

static void decrypt1GoBinaryFileParallel(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigzipfile";
    string pathInput = "../data/1GB.zip.rc4";
    string pathOutput = "../data/1GB.zip.rc4.decrypt";

    for (auto _ : state) {
        FileAccessor fileAccessor(pathInput, pathOutput);
        ThreadManager tm(&fileAccessor, nbThread, key);
        tm.startWork();
    }
}
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//Tiny Text Sequential Benchmark
BENCHMARK(encryptTinyTextFileOneThread);
BENCHMARK(decryptTinyTextFileOneThread);
//Tiny Text Parallel Benchmark
BENCHMARK(encryptTinyTextFileParallel);
BENCHMARK(decryptTinyTextFileParallel);

//Big Text Sequential Benchmark
BENCHMARK(encryptBigTextFileOneThread);
BENCHMARK(decryptBigTextFileOneThread);
//Big Text Parallel Benchmark
BENCHMARK(encryptBigTextFileParallel);
BENCHMARK(decryptBigTextFileParallel);

//Big Binary Sequential Benchmark
BENCHMARK(encryptBigBinaryFileOneThread);
BENCHMARK(decryptBigBinaryFileOneThread);
//Big Binary Parallel Benchmark
BENCHMARK(encryptBigBinaryFileParallel);
BENCHMARK(decryptBigBinaryFileParallel);

//1Gb Binary Parallel benchmark
BENCHMARK(encrypt1GoBinaryFileParallel);
BENCHMARK(decrypt1GoBinaryFileParallel);
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//Launch all the benchmarks
BENCHMARK_MAIN();