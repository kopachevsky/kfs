#include "xglfs_chown.h"

int xglfs_chown(const char *path, uid_t uid, gid_t gid) {
    int res = glfs_chown(XGLFS_STATE->fs, path, uid, gid);
    printf("xglfs_chown execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
