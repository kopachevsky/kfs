#include "xglfs_create.h"

int xglfs_create(const char* _path, mode_t _mode, struct fuse_file_info* _info) {
    int ret = 0;
    glfs_fd_t* fd = glfs_creat(XGLFS_STATE->fs, _path, O_CREAT | O_WRONLY | O_TRUNC, _mode);
    if (unlikely(!fd)) {
        ret = -errno;
    }
    if (likely(ret == 0)) {
        _info->fh = FD_TO_FH(fd);
    }
    return ret;
}