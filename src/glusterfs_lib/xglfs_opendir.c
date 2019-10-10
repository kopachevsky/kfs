#include "xglfs_opendir.h"

int xglfs_opendir(const char *path, struct fuse_file_info *fi) {
    (void)fi;
    glfs_fd_t* fd = glfs_opendir(XGLFS_STATE->fs, path);
    if (unlikely(!fd)) {
        return -errno;
    }
    XGLFS_STATE->g_fh = FD_TO_FH(fd);
    return 0;
}
