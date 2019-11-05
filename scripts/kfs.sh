#!/bin/bash

#
cd /workdir/
git clone https://github.com/kopachevsky/kfs.git

#
cd /workdir/kfs/
mkdir build && cd build
cmake .. && make

#
cd /workdir/kfs/build/src
./kfs --mountpoint=/mnt/mount --cache=/mnt/cache

#
cd /mnt/mount
prove -rv /workdir/pjdfstest/tests
