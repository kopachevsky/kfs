#include "xglfs_fsync.h"

int xglfs_fsync(const char* _path, int _datasync, struct fuse_file_info* _info) {
    (void)_path;
    int ret = 0;

    if (_datasync)
        ret = glfs_fdatasync(FH_TO_FD(_info->fh));
    else
        ret = glfs_fsync(FH_TO_FD(_info->fh));
    if (unlikely(ret < 0))
        ret = -errno;

    return ret;
}
