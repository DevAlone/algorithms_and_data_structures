#!/usr/bin/env bash

rm ./a.out &> /dev/null; g++ -lpthread -O3 -o a.out *.cpp && nice -n -20 ./a.out