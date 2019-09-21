#include "xglfs_fgetattr.h"

int xglfs_fgetattr(const char* _path, struct stat* _statbuf, struct fuse_file_info* _info) {
    int res = 0;
    if (!strcmp(_path, "/")) {
        res = xglfs_getattr(_path, _statbuf);
    } else {
        res = glfs_fstat(FH_TO_FD(_info->fh), _statbuf);
        if (unlikely(res < 0)) {
            res = -errno;
        }
    }
    return res;
}

