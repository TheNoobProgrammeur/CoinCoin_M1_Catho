//
// Created by Antoine on 19/04/2020.
//

#include <cstring>
#include <iostream>
#include <random>

#include "miner.h"

using namespace std;

#ifndef COINCOIN_COINMINER_H
#define COINCOIN_COINMINER_H

#define HASH_SIZE 20
#define TOKEN_SIZE 60 + 1 // On compte le \0

class Coinminer : Miner {
    int min_c_indice;
    bool min_c_isleft;
    char token[TOKEN_SIZE];
    bool is_token_valide;
    unsigned char hash[HASH_SIZE];
    random_device rd;
    minstd_rand gen;
    uniform_int_distribution<int> dist;

    long token_created;
    bool is_mining;


public:
    Coinminer(string trigram, int min_c_to_found);
    void start(void) override;
    void benchmark(int benchmark_time) override;
    void stop(void) override;


private:
    void process_benchmark(int benchmark_time);
    void write_token() override;
    void hash_token() override;
    void evaluate_hash() override;
};

#endif //COINCOIN_COINMINER_H
