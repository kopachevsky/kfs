#include "kfs_access.h"

int kfs_access(const char* path, int mask) {
    int grant = 1;
    if(grant) return(0);
    return(-EACCES);
}