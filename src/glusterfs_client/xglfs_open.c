#include "xglfs_open.h"

int xglfs_open(const char* _pathname, struct fuse_file_info* _info) {
    int ret = 0;
    glfs_fd_t* fd = NULL;

    if ((_info->flags & O_CREAT) == O_CREAT)
        fd = glfs_creat(XGLFS_STATE->fs, _pathname, _info->flags, 0);
    else
        fd = glfs_open(XGLFS_STATE->fs, _pathname, _info->flags);
    if (unlikely(!fd))
        ret = -errno;

    if (likely(ret == 0))
        XGLFS_STATE->g_fh = FD_TO_FH(fd);
    printf("xglfs_open fd : %lu\n", XGLFS_STATE->g_fh);

    return ret;
}