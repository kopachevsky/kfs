#include <kfs_chown.h>

int kfs_chown(const char *path, uid_t uid, gid_t gid) {
    int res = lchown(path, uid, gid);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
