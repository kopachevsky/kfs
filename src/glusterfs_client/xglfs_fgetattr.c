#include "xglfs_fgetattr.h"

int xglfs_fgetattr(const char* _path, struct stat* _statbuf, struct fuse_file_info* _info) {
    int ret = 0;

    if (!strcmp(_path, "/"))
        ret = xglfs_getattr(_path, _statbuf);
    else
    {
        ret = glfs_fstat(FH_TO_FD(_info->fh), _statbuf);
        if (unlikely(ret < 0))
            ret = -errno;
    }

    return ret;
}

