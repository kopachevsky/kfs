#include "xglfs_releasedir.h"

int xglfs_releasedir(const char* _path, struct fuse_file_info* _info) {
    (void)_path;
    int ret = 0;

    ret = glfs_closedir(FH_TO_FD(_info->fh));
    if (unlikely(ret < 0))
        ret = -errno;

    return ret;
}

