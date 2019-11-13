#include "kfs_releasedir.h"

int kfs_releasedir(const char *path, struct fuse_file_info *fi) {
    log_info("kfs_releasedir start");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_releasedir path : %s\n", fpath);
    log_debugf("    kfs_releasedir fd : %lu\n", fi->fh);
    (void) fpath;
    set_current_user();
    int fd = closedir((DIR *) (uintptr_t) fi->fh);
    set_default_user();
    if (fd == -1) {
        log_debugf("Error kfs_releasedir : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_releasedir exit result : %d\n", fd);
    return 0;
}