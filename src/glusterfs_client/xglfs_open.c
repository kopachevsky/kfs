#include "xglfs_open.h"

int xglfs_open(const char* _pathname, struct fuse_file_info* _info) {
    glfs_fd_t* g_fd = NULL;
    if ((_info->flags & O_CREAT) == O_CREAT) {
        g_fd = glfs_creat(XGLFS_STATE->fs, _pathname, _info->flags, 0);
    } else {
        g_fd = glfs_open(
                XGLFS_STATE->fs, _pathname, _info->flags);
    }
    if (unlikely(!g_fd)) {
        return  -errno;
    }
    _info->fh_old = FD_TO_FH(g_fd);
    printf("xglfs gluster fd : %lu\n",  _info->fh_old);
    return 0;
}