#include <kfs_truncate.h>

int kfs_truncate(const char *path, off_t offset) {
    return truncate(concat(ABSOLUTE_PATH, path), offset);
}
