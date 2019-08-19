cd .. && cd zlog && make && make install && cd .. && cd workdir
cd /usr/local/lib && /sbin/ldconfig -v && cd - 
mkdir build && cd build
cmake .. && make
cd -
