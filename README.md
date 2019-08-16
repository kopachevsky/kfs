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

Build issues:

    zlog:

error while loading shared libraries: libzlog.so.1.2: cannot open shared object file: No such file or directory - resolved by running sudo /sbin/ldconfig -v in /usr/local/lib

