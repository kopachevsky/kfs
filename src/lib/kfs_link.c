#include "kfs_link.h"

int kfs_link(const char* source_path, const char* target_path) {
    int res = link(source_path, target_path);
    if (res == -1) {
        return -errno;
    }
    return 0;
}