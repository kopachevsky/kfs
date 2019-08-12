#include "kfs_opendir.h"

int kfs_opendir(const char* original_path, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    DIR *dp = opendir(path);
    if (dp == NULL) {
        return -errno;
    }
    fi->fh = (intptr_t) dp;
    free(path);
    return 0;
}


