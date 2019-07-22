Dependencies:

    sudo ./install_dependencies.sh

Build:
    
    1.mkdir build && cd build
    2.cmake.. && make
    /or use ./scripts/build.sh 

Mount:

    ./build/KFS -d -s -f <directory>

Unmount:

    fusermount -uz <directory>

How to check mount:

    findmnt

Test:

    make & make test

To check tests results:

    ${BUILD_DIR}/Testings/test.log

