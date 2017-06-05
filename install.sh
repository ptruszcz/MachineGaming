#!/bin/bash
sudo apt install cmake python3-dev python3-pip python3-tk libboost-python-dev libboost-serialization-dev libboost-test-dev libarmadillo-dev
sudo pip3 install pygame matplotlib
mkdir bin
cd bin
rm -rf *
cmake -DCMAKE_BUILD_TYPE=Release -G Unix\ Makefiles ../
make -j 4
echo -e DONE!
