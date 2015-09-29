#! /bin/sh
if [ ! -d "build" ]; then
    mkdir build
fi

cd build
cmake ../src/ || exit 1
make || exit 1
sudo make install

