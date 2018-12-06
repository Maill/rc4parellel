//
// Created by olivier on 28/11/18.
//

#include <benchmark/benchmark.h>
#include "../src/Functions.h"

using namespace Functions;

//////////////////////////////////////////////////////////////
static void encryptTinyTextFileSequential(benchmark::State& state) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/1_input";
    string pathOutput = "../data/2_input";

    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWorkSequential(pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}

static void decryptTinyTextFileSequential(benchmark::State& state) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/2_input";
    string pathOutput = "../data/2_output";

    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWorkSequential(pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
static void encryptTinyTextFileParallel(benchmark::State& state) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/1_input";
    string pathOutput = "../data/2_input";
    int nbThread = 3;

    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWork(nbThread, pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}

static void decryptTinyTextFileParallel(benchmark::State& state) {
    //Variable init
    string key = "iamarandomkey";
    string pathInput = "../data/2_input";
    string pathOutput = "../data/2_output";
    int nbThread = 3;
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWork(nbThread, pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
static void encryptBigTextFileSequential(benchmark::State& state) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/3_input";
    string pathOutput = "../data/4_input";
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWorkSequential(pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}

static void decryptBigTextFileSequential(benchmark::State& state) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/4_input";
    string pathOutput = "../data/4_output";
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWorkSequential(pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
static void encryptBigTextFileParallel(benchmark::State& state) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/3_input";
    string pathOutput = "../data/4_input";
    int nbThread = 3;
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWork(nbThread, pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}

static void decryptBigTextFileParallel(benchmark::State& state) {
    //Variable init
    string key = "iamananotherrandomkey";
    string pathInput = "../data/4_input";
    string pathOutput = "../data/4_output";
    int nbThread = 3;
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWork(nbThread, pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
static void encryptBigBinaryFileSequential(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/5_input.jpg";
    string pathOutput = "../data/6_input";
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWorkSequential(pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}

static void decryptBigBinaryFileSequential(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/6_input";
    string pathOutput = "../data/6_output.jpg";
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWorkSequential(pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
static void encryptBigBinaryFileParallel(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/5_input.jpg";
    string pathOutput = "../data/6_input";
    int nbThread = 3;
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWork(nbThread, pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}

static void decryptBigBinaryFileParallel(benchmark::State& state) {
    //Variable init
    string key = "akeyforabigphoto";
    string pathInput = "../data/6_input";
    string pathOutput = "../data/6_output.jpg";
    int nbThread = 3;
    
    for (auto _ : state) {
        //RC4 work
        map<int, pair<int, unsigned char*>> parts = launchWork(nbThread, pathInput, key);
        writeIntoFile(parts, pathOutput, (int)getStringFromFile(pathInput).length());
    }
}
//////////////////////////////////////////////////////////////

//Tiny Text Sequential Benchmark
BENCHMARK(encryptTinyTextFileSequential);
BENCHMARK(decryptTinyTextFileSequential);
//Tiny Text Parallel Benchmark
BENCHMARK(encryptTinyTextFileParallel);
BENCHMARK(decryptTinyTextFileParallel);

//Big Text Sequential Benchmark
BENCHMARK(encryptBigTextFileSequential);
BENCHMARK(decryptBigTextFileSequential);
//Big Text Parallel Benchmark
BENCHMARK(encryptBigTextFileParallel);
BENCHMARK(decryptBigTextFileParallel);

//Big Binary Sequential Benchmark
BENCHMARK(encryptBigBinaryFileSequential);
BENCHMARK(decryptBigBinaryFileSequential);
//Big Binary Parallel Benchmark
BENCHMARK(encryptBigBinaryFileParallel);
BENCHMARK(decryptBigBinaryFileParallel);

BENCHMARK_MAIN();