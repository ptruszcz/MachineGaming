#!/bin/bash
# bash script here
sudo apt install cmake python3-dev python3-pip libboost-all-dev libarmadillo-dev
sudo pip3 install pygame
mkdir bin
cd bin
rm -rf *
cmake -G Unix\ Makefiles ../
make -j 4
echo -e DONE!
