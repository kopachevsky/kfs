#include "kfs_unlink.h"

int kfs_unlink(const char* path) {
    int res = 0;
    res = unlink(path);
        if (res == -1)
            return -errno;
    return 0;
}


