# Found from the Turtlecoin GitHub
# Copyright (c) The TurtleCoin Developers
# Copyright (c) The Amity Developers

sudo apt-get update 
yes "" | sudo apt-get install build-essential python-dev gcc gcc-7 cpp g++ cpp-7 g++-7 git cmake libboost1.58-all-dev librocksdb-dev 
export CXXFLAGS="-std=gnu++11" 
mkdir build && cd $_ 
cmake .. 
make
