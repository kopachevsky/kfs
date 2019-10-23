#include "kfs_symlink.h"

int kfs_symlink(const char *source_path, const char *target_path) {
    char fs_source_path[MAX_PATH];
    char fs_target_path[MAX_PATH];
    fullpath(fs_source_path, source_path);
    fullpath(fs_target_path, target_path);
    int res = symlink(fs_source_path, fs_target_path);
    printf("kfs_symlink execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_symlink(source_path, target_path);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}