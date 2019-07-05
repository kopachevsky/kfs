cmake -DCMAKE_BUILD_TYPE=Debug . -Bbuild
cd build
make -j 
cd -
mkdir -p bin
cp build/bin/kfs bin 

