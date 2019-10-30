#include "kfs_link.h"

int kfs_link(const char *source_path, const char *target_path) {
    char fs_source_path[PATH_MAX];
    char fs_target_path[PATH_MAX];
    fullpath(fs_source_path, source_path);
    fullpath(fs_target_path, target_path);
    log_debugf("kfs_link source_path: %s\n", fs_source_path);
    log_debugf("kfs_link target_path: %s\n", fs_target_path);
    int res = link(fs_source_path, fs_target_path);
    log_debugf("kfs_link execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_link : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_link(source_path, target_path);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}