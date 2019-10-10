#include "xglfs_release.h"

int xglfs_release(const char *path, struct fuse_file_info *fi) {
    (void)path;
    (void)fi;
    printf("xglfs_release local fd : %lu\n", XGLFS_STATE->g_fh);
    int res = glfs_close(FH_TO_FD(XGLFS_STATE->g_fh));
    if (res == -1) {
        return -errno;
    }
    return 0;
}