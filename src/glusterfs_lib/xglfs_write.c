#include "xglfs_write.h"

int xglfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    (void)path;
    (void)fi;
    printf("xglfs_write fd : %lu\n", XGLFS_STATE->g_fh);
    int res = glfs_pwrite(FH_TO_FD(XGLFS_STATE->g_fh), buf, size, offset, 0);
    printf("xglfs_open execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return res;
}

