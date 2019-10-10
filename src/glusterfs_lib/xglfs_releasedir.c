#include "xglfs_releasedir.h"

int xglfs_releasedir(const char *path, struct fuse_file_info *fi) {
    (void)path;
    (void)fi;
    int res = glfs_closedir(FH_TO_FD(XGLFS_STATE->g_fh));
    if (res == -1) {
        return -errno;
    }
    return 0;
}

