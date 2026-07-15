# bin/bash
g++ -o lab.out -std=c++20 -O3 lab9.cpp -lgsl -lgslcblas -lm
./lab.out
python3 plot.py
