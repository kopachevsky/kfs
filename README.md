Build:
    
    1.mkdir build && cd build
    2.cmake.. && make
    /or use build.sh

Mount/Unmount

To mount fs use:
    ./build/KFS -d -s -f <directory>
to unmount fs use:
    fusermount -uz <directory>

How to check mount:

    findmnt
