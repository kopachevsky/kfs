#include <kfs_releasedir.h>

int kfs_releasedir(const char *original_path, struct fuse_file_info* fi) {
    char *path = local_disk_cache_path(original_path);
    (void) path;
    int fd = closedir((DIR *) (uintptr_t) fi->fh);
    if (fd == -1) {
        return -errno;
    }
    free(path);
    return 0;
}