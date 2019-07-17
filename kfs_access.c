#include "kfs_access.h"

int kfs_access(const char* _path, int _mask) {
    int grant = 1;
    if(grant) return(0);
    return(-EACCES);
}