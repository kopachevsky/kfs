#include "xglfs_open.h"

int xglfs_open(const char* _pathname, struct fuse_file_info* _info) {
    int res = 0;
    glfs_fd_t* fd = NULL;
    fd = (_info->flags & O_CREAT) == O_CREAT ? glfs_creat(XGLFS_STATE->fs, _pathname, _info->flags, 0) : glfs_open(
            XGLFS_STATE->fs, _pathname, _info->flags);
    if (unlikely(!fd)) {
        res = -errno;
    }
    if (likely(res == 0)) {
        _info->fh = FD_TO_FH(fd);
    }
    printf("xglfs gluster fd : %lu ",  FD_TO_FH(fd));
    return res;
}