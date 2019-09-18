#include "xglfs_fsync.h"

int xglfs_fsync(const char* _path, int _datasync, struct fuse_file_info* _info) {
    (void)_path;
    int ret = _datasync ? glfs_fdatasync(FH_TO_FD(_info->fh), NULL, NULL) : glfs_fsync(FH_TO_FD(_info->fh), NULL, NULL);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}
