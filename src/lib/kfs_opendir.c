#include "kfs_opendir.h"

int kfs_opendir(const char* path, struct fuse_file_info *fi) {
    DIR *dp = opendir(path);
    if (dp == NULL) {
        return -errno;
    }
    fi->fh = (intptr_t) dp;
    return 0;
}


