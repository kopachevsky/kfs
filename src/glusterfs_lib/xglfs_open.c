#include "xglfs_open.h"

int xglfs_open(const char *path, struct fuse_file_info *fi) {
    int res = 0;
    glfs_fd_t* fd = glfs_open(XGLFS_STATE->fs, path, fi->flags);
    if (unlikely(!fd)) {
        res = -errno;
    }
    if (likely(res == 0)) {
        XGLFS_STATE->g_fh = FD_TO_FH(fd);
    }
    printf("xglfs_open fd : %lu\n", XGLFS_STATE->g_fh);
    return res;
}