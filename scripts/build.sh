mkdir build && cd build
cmake .. && make
cd -
cd /tmp && mkdir kfs && mkdir log  && cd kfs && mkdir CACHE && mkdir MOUNTPOINT && cd .. && cd log && touch mylog.txt && cd- 
