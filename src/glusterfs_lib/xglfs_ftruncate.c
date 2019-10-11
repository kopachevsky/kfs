#include "xglfs_ftruncate.h"

int xglfs_ftruncate(const char *path, off_t size, struct fuse_file_info *fi) {
    (void)path;
    (void)fi;
    printf("xglfs_ftruncate fd : %lu\n", XGLFS_STATE->g_fh);
    int res = glfs_ftruncate(FH_TO_FD(XGLFS_STATE->g_fh), size);
    printf("xglfs_ftruncate execute result : %d\n", res);
    if (unlikely(res < 0)) {
        int saved_errno = errno;
        glfs_close(FH_TO_FD(XGLFS_STATE->g_fh));
        res = -saved_errno;
    } else {
        res = glfs_close(FH_TO_FD(XGLFS_STATE->g_fh));
        if (unlikely(res < 0)) {
            return -errno;
        }
    }
    return 0;
}
