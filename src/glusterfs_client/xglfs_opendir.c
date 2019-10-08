#include "xglfs_opendir.h"

int xglfs_opendir(const char* _path, struct fuse_file_info* _info) {
    glfs_fd_t* fd = glfs_opendir(XGLFS_STATE->fs, _path);
    if (unlikely(!fd)) {
        return -errno;
    }
    _info->fh = FD_TO_FH(fd);
    return 0;
}
