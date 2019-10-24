#!/bin/bash
set -e
echo "Disc setup"

mkdir -p /data/brick1
gluster volume create gv0  server1:/data/brick1/gv0 force
gluster volume start gv0
gluster volume status gv0

