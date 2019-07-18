Build:
    
    1.mkdir build && cd build
    2.cmake.. && make
    /or use build.sh

Mount:

    ./build/KFS -d -s -f <directory>

Unmount:

    fusermount -uz <directory>

How to check mount:

    findmnt
