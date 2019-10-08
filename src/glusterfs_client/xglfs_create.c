#include "xglfs_create.h"

int xglfs_create(const char* _path, mode_t _mode, struct fuse_file_info* _info) {
    glfs_fd_t* g_fd = glfs_creat(XGLFS_STATE->fs, _path, _info->flags, _mode);
    if (unlikely(!g_fd)) {
        return  -errno;
    }
    _info->fh = FD_TO_FH(g_fd);
    printf("gluster create fd : %lu\n", _info->fh);
    return 0;
}
