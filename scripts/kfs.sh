#!/bin/bash

#create needed directories
mkdir -p /mnt/mount /mnt/cache /tmp/log /workdir
touch /tmp/log/mylog.txt

#clone and install zlog
cd /workdir
git clone https://github.com/HardySimpson/zlog.git 
cd zlog 
make
make install
cd /usr/local/lib
/sbin/ldconfig -v

#clone and install pjdfstest
cd /workdir
git clone https://github.com/pjd/pjdfstest.git
cd /workdir/pjdfstest
autoreconf -ifs
./configure
make pjdfstest

#clone and install kfs
cd /workdir
git clone https://github.com/kopachevsky/kfs.git
cd /workdir/kfs/
mkdir build
cd build
cmake ..
make

#start kfs and mount to /mnt/mount
cd /workdir/kfs/build/src
./kfs --mountpoint=/mnt/mount --cache=/mnt/cache

#start pjdfstest
cd /mnt/mount
prove -rv /workdir/pjdfstest/tests
