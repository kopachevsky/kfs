Dependencies:

    sudo ./install_dependencies.sh

Build:
    
    1.mkdir build && cd build
    2.cmake.. && make
    /or use ./scripts/build.sh 

Mount:

    ./build/src/kfs -d -s <directory>

Unmount:

    fusermount -u <directory>

How to check mount:

    findmnt

Test:

    cd /build && make && make test

To check tests results:

    ${BUILD_DIR}/Testings/test.log

Docker:

    to run image - docker run -it --privileged --rm -v /PATH_TO_kfs/:/home/ubuntu/workdir IMAGE_NAME /bin/bash

Build issues:

    zlog:

error while loading shared libraries: libzlog.so.1.2: cannot open shared object file: No such file or directory - resolved by running sudo /sbin/ldconfig -v in /usr/local/lib

