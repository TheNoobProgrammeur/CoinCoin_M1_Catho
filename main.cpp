/**
* @author Antoine Berthier
* @date 2020
*/

#include <iostream>
#include <signal.h>

#include "coinminer.h"

using namespace std;

bool arg_z = false;
bool arg_t = false;
bool arg_m = false;
string trigram("ABR");
int min_c_to_found = 1;
Coinminer *coinminer;

void my_handler(int s);
void parse_args(int argc, char **argv);
void fatalError(string msg);

class ParseArgErrorExeption {
public:
    string message;

    ParseArgErrorExeption() {
        message = "Error";
    }

    ParseArgErrorExeption(string msg) {
        message = msg;
    }
};

int main(int argc, char** argv) {

    // Gestion ctrl+c

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    // parse args
    parse_args(argc, argv);

    // Lancement du mineur
    coinminer = new Coinminer(trigram, min_c_to_found);
    if (!arg_z) {
        coinminer->start();
    } else {
        cout << "Benchmark en cours..." << endl;
        coinminer->benchmark(50);
    }

    return 0;
}

void my_handler(int s) {
    coinminer->stop();
}

void parse_args(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        try {
            if (argv[i][0] != '-') {
                throw ParseArgErrorExeption("Vous devez mettre un '-' devant le paramètre");
            }
            switch (argv[i][1]) {
                case 'z':
                    arg_z = true;
                    break;
                case 't':
                    arg_t = true;
                    if (argc > i + 1) {
                        trigram = string(argv[++i]);
                        if (trigram.length() != 3) {
                            throw ParseArgErrorExeption("Le trigramme doit être composé de 3 lettres");
                        }
                    } else {
                        throw ParseArgErrorExeption("Vous devez mettre un trigramme en paramètre après -t");
                    }
                    break;
                case 'm':
                    arg_m = true;
                    if (argc > i + 1) {
                        min_c_to_found = stoi(string(argv[++i]));
                        if (min_c_to_found < 1 || min_c_to_found > 11) {
                            throw ParseArgErrorExeption("Argument de -m dois être entre 1 et 11");
                        }
                    } else {
                        throw ParseArgErrorExeption("Vous devez mettre un nombre en paramètre après -m");
                    }
                    break;
                default:
                    throw ParseArgErrorExeption("Paramètre non valide");
            }
        } catch (ParseArgErrorExeption e) {
            fatalError(e.message);
        } catch (invalid_argument const &e) {
            fatalError("L'argument -m n'est pas un nombre !");
        } catch (out_of_range const &e) {
            fatalError("L'argument -m ne respecte pas les bornes [1:11] !");
        }
    }

    if((!arg_z && (!arg_m || !arg_t)) || (arg_z && arg_m && arg_t)) {
        fatalError("Paramètres non cohérents");
    }
}

void fatalError(string msg) {
    cout << "[Erreur] Coinminer : " << msg << endl;
    exit(1);
}
