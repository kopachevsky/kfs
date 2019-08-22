#include "kfs_symlink.h"

int kfs_symlink(const char* source_path, const char* target_path) {
    int res = symlink(source_path, target_path);
    if (res == -1) {
        return -errno;
    }
    return 0;
}