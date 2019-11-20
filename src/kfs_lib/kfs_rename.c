#include "kfs_rename.h"

int kfs_rename(const char *source_path, const char *target_path) {
    log_debugf("kfs_rename start  %s\n", source_path);
    char fs_source_path[PATH_MAX_EXTENDED] = {0};
    char fs_target_path[PATH_MAX_EXTENDED] = {0};
    fullpath(fs_source_path, source_path);
    fullpath(fs_target_path, target_path);
    log_debugf("    kfs_rename full_source path : %s\n", fs_source_path);
    log_debugf("    kfs_rename full_target_path : %s\n", fs_target_path);
    set_current_user();
    fuse_context_log();
    int res = rename(fs_source_path, fs_target_path);
    set_default_user();
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
    log_debugf("kfs_rename exit result : %d\n", res);
    return 0;
}