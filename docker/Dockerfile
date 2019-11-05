FROM ubuntu:18.04

RUN set -e && \
    apt-get update && \
    apt-get install -y pkg-config uuid-dev && \
    apt-get install -y check cmake bison glusterfs-client libfuse-dev zlib1g-dev git && \
    apt-get install -y autoconf automake gcc make linux-headers-$(uname -r)

RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN set -e && \
    git clone https://github.com/HardySimpson/zlog.git && \
    cd zlog && make && make install && cd .. && cd /usr/local/lib && /sbin/ldconfig -v && cd -

ADD conf/zlog.conf ~/zlog.conf

RUN mkdir -p /mnt/mount && mkdir -p /mnt/cache && mkdir -p /tmp/log && touch /tmp/log/mylog.txt

RUN mkdir /workdir && cd /workdir && \
    git clone https://github.com/pjd/pjdfstest.git && \
    cd /workdir/pjdfstest && \
    autoreconf -ifs && ./configure && make pjdfstest

ADD scripts/kfs.sh /workdir/kfs.sh

WORKDIR /workdir
