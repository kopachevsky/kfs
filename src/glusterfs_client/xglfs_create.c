#include "xglfs_create.h"

int xglfs_create(const char* _path, mode_t _mode, struct fuse_file_info* _info) {
    int res = 0;
    glfs_fd_t* fd = glfs_creat(XGLFS_STATE->fs, _path, _info->flags, _mode);
    if (unlikely(!fd)) {
        res = -errno;
    }
    if (likely(res == 0)) {
        _info->fh = FD_TO_FH(fd);
    }
    return res;
}
