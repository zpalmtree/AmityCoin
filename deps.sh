# Found from the Turtlecoin GitHub
# Copyright (c) The TurtleCoin Developers
# Copyright (c) The Amity Developers

sudo apt-get update 
yes "" | sudo apt-get install build-essential python-dev gcc-4.9 g++-4.9 git cmake libboost1.58-all-dev librocksdb-dev 
export CXXFLAGS="-std=gnu++11" 
mkdir build && cd $_ 
cmake .. 
make
