#!/bin/bash 

cd "$( cd "$(dirname "$0")" && pwd)"

g++ -c decipher.h | g++ -c decipher.cpp -o decipher.o
g++ -c classes.h | g++ -c classes.cpp -o classes.o
ar -r cls.a classes.o decipher.o
g++ main_cpp.cpp cls.a -pthread -static -o decipherer