#include "xglfs_open.h"

int xglfs_open(const char* _pathname, struct fuse_file_info* _info) {
    int res = 0;
    glfs_fd_t* g_fd = NULL;
    g_fd = _info->flags == O_CREAT ? glfs_creat(XGLFS_STATE->fs, _pathname, _info->flags, 0) : glfs_open(
            XGLFS_STATE->fs, _pathname, _info->flags);
    if (unlikely(!g_fd)) {
        res = -errno;
    }
    if (likely(res == 0)) {
        _info->fh = FD_TO_FH(g_fd);
    }
    printf("xglfs gluster fd : %lu\n",  _info->fh);
    return res;
}