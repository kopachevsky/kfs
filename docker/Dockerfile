FROM ubuntu:18.04

RUN set -e && \
    apt-get update && \
    apt-get install -y pkg-config uuid-dev && \
    apt-get install -y check cmake bison glusterfs-client libfuse-dev zlib1g-dev git

RUN set -e && \
    git clone https://github.com/HardySimpson/zlog.git && \
    cd zlog && make && make install && cd .. && cd /usr/local/lib && /sbin/ldconfig -v && cd -

RUN useradd -rm -d /home/ubuntu -s /bin/bash -g root -G sudo -u 1000 ubuntu

USER ubuntu

RUN mkdir /home/ubuntu/workdir

WORKDIR /home/ubuntu/workdir