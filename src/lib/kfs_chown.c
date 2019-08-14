#include <kfs_chown.h>

int kfs_chown(const char *original_path, uid_t uid, gid_t gid) {
    char *path = local_disk_cache_path(original_path);
    int res = lchown(path, uid, gid);
    if (res == -1) {
        return -errno;
    }
    free(path);
    return 0;
}
