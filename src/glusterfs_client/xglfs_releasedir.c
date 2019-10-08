#include "xglfs_releasedir.h"

int xglfs_releasedir(const char* _path, struct fuse_file_info* _info) {
    (void)_path;
    int res = glfs_closedir(FH_TO_FD(_info->fh));
    if (res == -1) {
        return  -errno;
    }
    return 0;
}

