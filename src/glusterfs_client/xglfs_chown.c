#include "xglfs_chown.h"

int xglfs_chown(const char *path, uid_t uid, gid_t gid) {
    int res = glfs_chown(XGLFS_STATE->fs, path, uid, gid);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
