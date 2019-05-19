#!/usr/bin/env bash

rm ./a.out &> /dev/null; g++ -std=c++17 -lpthread -O3 -o a.out *.cpp && ./a.out
