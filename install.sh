#!/usr/bin/env bash

git clone --depth 1 https://github.com/himeyama/libgaussian.git /tmp/libgaussian
cd /tmp/libgaussian
make -j
sudo mkdir -p /usr/local/include
sudo cp gaussian.h /usr/local/include/
sudo cp libgaussian.so /usr/lib/
rm -rf /tmp/libgaussian
