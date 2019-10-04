#include "kfs_opendir.h"

int kfs_opendir(const char* path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    DIR *dp = opendir(fpath);
    fprintf(stderr,"%s\n", "kfs opendir");
    fprintf(stderr, "%d\n", -errno);
    if (dp == NULL) {
        return -errno;
    }
    fi->fh = (intptr_t) dp;
    if (XGLFS_STATE->gluster_api) {
        int res = xglfs_opendir(path, fi);
        fprintf(stderr,"%s\n", "xglfs opendir");
        fprintf(stderr, "%d\n", -errno);
        if (res == -1) {
            return -errno;
        }
    }
    return 0;
}


