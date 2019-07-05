 Build 

    cmake -DCMAKE_BUILD_TYPE=Debug . -Bbuild
    cd build
    make -j 

Mount

    ./bin/kfs -d -s -f <directory>
