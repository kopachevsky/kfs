#include "kfs_rename.h"

int kfs_rename(const char *source_path, const char *target_path) {
    char fs_source_path[PATH_MAX];
    char fs_target_path[PATH_MAX];
    fullpath(fs_source_path, source_path);
    fullpath(fs_target_path, target_path);
    log_debugf("kfs_rename source path : %s\n", fs_source_path);
    log_debugf("kfs_rename target_path : %s\n", fs_target_path);
    set_current_user();
    int res = rename(fs_source_path, fs_target_path);
    set_default_user();
    log_debugf("kfs_rename execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_rename : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_rename(source_path, target_path);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}