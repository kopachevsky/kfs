#include "kfs_opendir.h"

int kfs_opendir(const char* path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    DIR *dp = opendir(fpath);
    if (dp == NULL) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int res = xglfs_opendir(path, fi);
        if (res == -1) {
            return -errno;
        }
    }
    fi->fh = (intptr_t) dp;
    return 0;
}


