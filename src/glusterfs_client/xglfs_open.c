#include "xglfs_open.h"

int xglfs_open(const char* _pathname, struct fuse_file_info* _info) {
    int ret = 0;
    glfs_fd_t* fd = NULL;
    fd = (_info->flags & O_CREAT) == O_CREAT ? glfs_creat(XGLFS_STATE->fs, _pathname, _info->flags, 0) : glfs_open(
            XGLFS_STATE->fs, _pathname, _info->flags);
    if (unlikely(!fd)) {
        ret = -errno;
    }
    if (likely(ret == 0)) {
        _info->fh = FD_TO_FH(fd);
    }
    return ret;
}