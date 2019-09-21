#include "xglfs_release.h"

int xglfs_release(const char* _path, struct fuse_file_info* _info) {
    (void)_path;
    int ret = glfs_close(FH_TO_FD(_info->fh));
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}