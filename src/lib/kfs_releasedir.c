#include <kfs_releasedir.h>

int kfs_releasedir(const char *path, struct fuse_file_info* fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int fd = closedir((DIR *) (uintptr_t) fi->fh);
    if (fd == -1) {
        return -errno;
    }
    return 0;
}