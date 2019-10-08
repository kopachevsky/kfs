#include "xglfs_releasedir.h"

int xglfs_releasedir(const char* _path, struct fuse_file_info* _info) {
    (void)_path;
    int res = glfs_closedir(FH_TO_FD(_info->fh));
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return 0;
}

