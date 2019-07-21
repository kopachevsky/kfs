#include <kfs_truncate.h>

int kfs_truncate(const char *path, off_t offset) {
    return truncate(strcat(LOCAL_DISC_CACHE_PATH, path), offset);
}
