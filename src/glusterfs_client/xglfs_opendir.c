#include "xglfs_opendir.h"

int xglfs_opendir(const char* _path, struct fuse_file_info* _info) {
    int ret = 0;

    glfs_fd_t* fd = glfs_opendir(XGLFS_STATE->fs, _path);
    if (unlikely(!fd))
        ret = -errno;

    if (likely(ret == 0))
        _info->fh = FD_TO_FH(fd);

    return ret;
}
