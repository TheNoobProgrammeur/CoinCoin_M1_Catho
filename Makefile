CC=g++
CFLAG= -Werror -Wall -lcrypto -O3 -march=native


coin:
	$(CC) coinminer.cpp main.cpp $(CFLAG) -o coinminer

packages:
	sudo apt-get install libssl-dev g++ -y
