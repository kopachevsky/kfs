#include "xglfs_create.h"

int xglfs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    glfs_fd_t* fd = glfs_creat(XGLFS_STATE->fs, path, fi->flags, mode);
    if (unlikely(!fd)) {
        return -errno;
    }
    XGLFS_STATE->g_fh = FD_TO_FH(fd);
    printf("xglfs_create fd : %lu\n", XGLFS_STATE->g_fh);
    return 0;
}
