#include "xglfs_release.h"

int xglfs_release(const char* _path, struct fuse_file_info* _info) {
    (void)_path;
    int ret = 0;

    printf("xglfs_release local fd : %lu\n", XGLFS_STATE->g_fh);

    ret = glfs_close(FH_TO_FD(XGLFS_STATE->g_fh));
    if (unlikely(ret < 0))
        ret = -errno;

    return ret;
}