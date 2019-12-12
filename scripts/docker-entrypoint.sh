#!/bin/bash

#set gluster ip
echo "172.17.0.2      server1" >> /etc/hosts

# Start service
exec workdir/kfs/build/src/kfs --server=server1 --volume=gv0 --mountpoint=/mnt/data/ --cache=/mnt/cache --gluster_sync=true  
