#! /bin/bash

g++ -Wall -c hello.cxx
g++ -Wall -c greeting.cxx
g++ -Wall -c factorial.cxx
g++ hello.o greeting.o factorial.o -o hello
