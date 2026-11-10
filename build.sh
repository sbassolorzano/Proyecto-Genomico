#!/bin/bash
set -e
g++ -std=c++17 -O2 -Wall src/*.cpp -o genoma
./genoma data/HIV2_ALL_2021_env_DNA.2000.fasta
