FROM ubuntu:18.04

RUN set -x && \
    apt-get update && \
    apt-get install -y pkg-config uuid-dev && \
    apt-get install -y bison glusterfs-client libfuse-dev zlib1g-dev && \
    apt-get install -y check make cmake gcc autoconf automake && \
    apt-get install -y git vim && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN set -e && \
    touch /var/log/kfs.log && \
    mkdir -p /mnt/data /mnt/cache /workdir

RUN set -e && \
    cd /workdir && \
    git clone https://github.com/HardySimpson/zlog.git && \
    cd zlog && make && make install && \
    cd /usr/local/lib && /sbin/ldconfig -v

RUN set -e && \
    cd /workdir set -e && \
    git clone https://github.com/KostiaLevchenko/kfs.git && \
    cd /workdir/kfs/ && git checkout Feature/dockerfile_pre-mounted_file_system  && ./scripts/build.sh && \
    cp /workdir/kfs/conf/zlog.conf ~/zlog.conf

CMD set -e && \
    echo "172.17.0.2      server1" >> /etc/hosts &&  \
    /workdir/kfs/build/src/kfs --server=server1 --volume=gv0 --mountpoint=/mnt/data/ --cache=/mnt/cache/ --gluster_sync=true --foreground

