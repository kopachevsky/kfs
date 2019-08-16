FROM ubuntu:18.04

RUN set -e && \
    apt-get update && \
    apt-get install -y pkg-config uuid-dev && \
    apt-get install -y check cmake bison glusterfs-client libfuse-dev

RUN mkdir /workdir

WORKDIR /workdir