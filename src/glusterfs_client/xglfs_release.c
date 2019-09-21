#include "xglfs_release.h"

int xglfs_release(const char* _path, struct fuse_file_info* _info) {
    (void)_path;
    int res = glfs_close(FH_TO_FD(_info->fh));
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return res;
}