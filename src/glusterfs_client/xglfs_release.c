#include "xglfs_release.h"

int xglfs_release(const char* _path, struct fuse_file_info* _info) {
    (void)_path;
    printf("xglfs_release fd : %lu\n ", _info->fh);
    int res = glfs_close(FH_TO_FD(_info->fh));
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return 0;
}