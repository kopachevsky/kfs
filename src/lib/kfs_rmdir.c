#include <kfs_rmdir.h>

int kfs_rmdir(const char* original_path) {
    char *path = local_disk_cache_path(original_path);
    int res = rmdir(path);
    if(res == -1) {
        return errno;
    }
    return 0;
}

