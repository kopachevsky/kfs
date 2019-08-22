#include <kfs_rename.h>

int kfs_rename(const char* source_path, const char* target_path) {
    int res = rename(source_path, target_path);
    if (res == -1) {
        return -errno;
    }
    return 0;
}