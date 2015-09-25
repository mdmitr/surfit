#! /bin/sh
if [ ! -d "build" ]; then
    mkdir build
fi

cd build
cmake ../src/
make
sudo make install

