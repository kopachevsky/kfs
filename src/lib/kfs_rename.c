#include <kfs_rename.h>

int kfs_rename(const char* source_path, const char* target_path) {
    char *fs_source_path = local_disk_cache_path(source_path);
    char *fs_target_path = local_disk_cache_path(target_path);
    int res = rename(fs_source_path, fs_target_path);
    if (res == -1) {
        return -errno;
    }
    free(fs_source_path);
    free(fs_target_path);
    return 0;
}