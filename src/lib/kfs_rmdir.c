#include <kfs_rmdir.h>

int kfs_rmdir(const char* path) {
    int res = rmdir(path);
    if(res == -1) {
        return errno;
    }
    return 0;
}

