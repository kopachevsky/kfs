#include <kfs_rename.h>

int kfs_rename(const char* source_path, const char* target_path) {
    char fs_source_path[PATH_MAX];
    char fs_target_path[PATH_MAX];
    fullpath(fs_source_path, source_path);
    fullpath(fs_target_path, target_path);
    int res = rename(fs_source_path, fs_target_path);
    if (res == -1) {
        return -errno;
    }
    return 0;
}