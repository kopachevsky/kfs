apt-get update
apt-get install -y pkg-config uuid-devcheck cmake bison glusterfs-client libfuse-dev zlib1g-dev git 
cd / && git clone https://github.com/HardySimpson/zlog.git
cd zlog && make && make install && cd .. && cd /usr/local/lib && /sbin/ldconfig -v && cd -
