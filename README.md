# KFS

Dependencies:

    sudo ./scripts/install_dependencies.sh

Build:
    
    mkdir build && cd build
    cmake .. && make
    ../scripts/build.sh 

Mount:

    sudo ./build/src/kfs --server=<IP|DOMAIN> --volume=VOLUME --mountpoint=MOUNTPOINT --cache=CACHE_DISK --gluster_api=true [--protocol=<tcp|udp>] [--port=24007] [--logfile=<file|stderr|null>] [--verbosity=7] [--foreground]

Unmount:

    sudo fusermount -uz <directory>

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


# setup server docker

Start server docker in priveleged mode

    docker run -it -d --rm --privileged=true --hostname=server1 --name server1  gluster/gluster-centos 

    docker exec -it server1 bash

Find out server ip and add it to hosts file

    ip a | grep inet

    inet 127.0.0.1/8 scope host lo
    inet 172.18.0.2/16 brd 172.18.255.255 scope global eth0

    echo '172.18.0.2 server1' >> /etc/hosts

Create volume and start it

    mkdir -p /data/brick1

    gluster volume create gv0  server1:/data/brick1/gv0 force

    gluster volume start gv0

    gluster volume status gv0


Now we can run test client to check our server

    docker run -it --privileged --rm gluster/glusterfs-client bash

Put server IP from above to hosts file

    echo '172.18.0.2 server1' >> /etc/hosts

Mount and create test file in /mnt/gluster 

    mkdir /mnt/gluster
    mount -t glusterfs server1:/gv0 /mnt/gluster

    thouch /mnt/gluster/test

Exit glusterfs-client docker and start it again to have new and clean one.
Repeat setup and check chat "test" file will exists in /mnt/gluster folder

# New process

Build docker container:

    docker build -f docker/Dockerfile -t kfs-test .

Start docker container:

    docker run -it --privileged --name kfs-test --rm kfs-test /bin/bash
    
Run script to bulld kfs and start test:

    /workdir/kfs.sh

    
 
sudo /1-prj/dedicatted/kfs/build/src/kfs --mountpoint=/kfs/m2/ --cache=/kfs/cache --foreground



