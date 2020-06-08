//
// Created by Antoine on 19/04/2020.
//

// Avoir openssl installer sur la machine
// A compiler avec le flag -lcrypto
#include <openssl/sha.h>
#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <random>

#include "coinminer.h"

using namespace std;

Coinminer::Coinminer(string trigram, int min_c_to_found) : gen{rd()}, dist{32, 126} {
    token_created = 0;
    is_mining = true;
    if ( min_c_to_found % 2 == 0 ) {
        min_c_indice = (min_c_to_found / 2) - 1;
        min_c_isleft = false;
    } else {
        min_c_indice = floor(min_c_to_found / 2);
        min_c_isleft = true;
    }
    strcat(token, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"); // Nonce (32)
    strcat(token, "-");
    strcat(token, trigram.c_str()); // TriOwn (3)
    strcat(token, "-");
    strcat(token, "CC1.0"); // Proto (5)
    strcat(token, "-");
    strcat(token, to_string(time(NULL)).c_str()); // Time (10)
    strcat(token, "-");
    strcat(token, "0f0f0f"); // Reserved (6)
}

void Coinminer::start() {
    while (is_mining) {
        write_token();
        hash_token();
        evaluate_hash();

        if (is_token_valide) {
            cout << token << endl;
        }
    }
}

void Coinminer::benchmark(int benchmark_time) {
    time_t t1, t2;
    t1 = time(NULL);
    t2 = time(NULL);

    while (t1 - t2 < benchmark_time && is_mining) {
        write_token();
        hash_token();
        evaluate_hash();
        t1 = time(NULL);

        token_created++;
    }
    if (is_mining) {
        process_benchmark(benchmark_time);
    }
}

void Coinminer::stop() {
    is_mining = false;
}

void Coinminer::write_token() {
    for (int i = 0; i < 32; i++) {
        token[i] = char(dist(gen));
    }
}

void Coinminer::hash_token() {
    SHA1((unsigned char*)token, TOKEN_SIZE - 1, hash);
}


void Coinminer::evaluate_hash() {
    is_token_valide = true;

    for (int i = 0; i < min_c_indice; i++) {
        if ((hash[i] ^ 0xCC) != 0) {
            is_token_valide = false;
            return;
        }
    }

    if (!min_c_isleft && (hash[min_c_indice] ^ 0xCC) != 0) {
        is_token_valide = false;
    } else if (min_c_isleft && ((hash[min_c_indice] ^ 0xC0) < 0x0 || (hash[min_c_indice] ^ 0xC0) > 0xF)) {
        is_token_valide = false;
    }
}

void Coinminer::process_benchmark(int benchmark_time) {

    cout << "--------- Rapport Benchmark (" << benchmark_time << " seconds) ---------" << endl;
    cout <<  token_created << " tokens au total" << endl;
    token_created /= benchmark_time;
    cout <<  token_created << " tokens créés en moyenne par seconde" << endl;

    /**
     * chance d'avoir un P(c) = 1/16
     * P(xc) = 1/(16^x)
     */

    float pbn = pow(16.0,6.0);
    float pb =  token_created/pbn;

    cout << "-- Prévisions --" << endl;
    cout << "Subcoin (6c) trouvables en 1 heure : " << pb*3600 << endl;
    pbn *= 16;
    pb =  token_created/pbn;
    cout << "Coin (7c) trouvables en 10 heures : " << pb*36000 << endl;
    pbn *= 16;
    pb =  token_created/pbn;
    cout << "Hexcoin (8c) trouvables en 1 jour : " << pb*86400 << endl;
    pbn *= 16;
    pb =  token_created/pbn;
    cout << "Arkenstone (9c) trouvables en 7 jours : " << pb*604800 << endl;
    pbn *= 16;
    pb =  token_created/pbn;
    cout << "Blackstar (10c) trouvables en 1 mois : " << pb*604800*30 << endl;
    pbn *= 16;
    pb =  token_created/pbn;
    cout << "Grand Cross  (11c) trouvables en 1 mois : " << pb*604800*30 << endl;
}
