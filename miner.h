//
// Created by Antoine on 20/04/2020.
//
#include <cstring>

#ifndef COINCOIN_MINER_H
#define COINCOIN_MINER_H

using namespace std;

class Miner {

public:
    virtual void start(void) = 0;
    virtual void benchmark(int benchmark_time) = 0;
    virtual void stop(void) = 0;

private:
    virtual void write_token() = 0;
    virtual void hash_token() = 0;
    virtual void evaluate_hash() = 0;
};

#endif
