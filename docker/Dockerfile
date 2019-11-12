FROM ubuntu:18.04

RUN set -x && \
    apt-get update && \
    apt-get install -y pkg-config uuid-dev && \
    apt-get install -y bison glusterfs-client libfuse-dev zlib1g-dev && \
    apt-get install -y check make cmake gcc autoconf automake && \
    apt-get install -y git vim && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

COPY conf/zlog.conf ~/zlog.conf

COPY scripts/kfs.sh /workdir/kfs.sh
