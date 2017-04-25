#!/bin/bash
# bash script here
chmod a+x run.sh
sudo apt install cmake python3-dev libboost-all-dev libarmadillo-dev
mkdir bin
cd bin
rm -rf *
cmake -G Unix\ Makefiles ../
make -j 4
echo -e DONE!
